include_directories(
include
${GLEW_INCLUDE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_BINARY_DIR}/src/fade2d
${CMAKE_SOURCE_DIR}/dep/glfw/include
${CMAKE_SOURCE_DIR}/dep/glm
${CMAKE_SOURCE_DIR}/dep/stb
)

configure_file(shaderpath.h.in shaderpath.h)

file(GLOB src *.h *.cpp)

add_library(Fade2D ${src} ${CMAKE_BINARY_DIR}/src/fade2d/shaderpath.h)

add_dependencies(Fade2D glfw)

target_link_libraries(Fade2D glfw ${GLEW_LIBRARY} ${GLFW_LIBRARIES})


