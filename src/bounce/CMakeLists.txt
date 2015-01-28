include_directories(
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/dep/stb
${CMAKE_BINARY_DIR}/src/bounce/
${CMAKE_SOURCE_DIR}/dep/rapidxml
${CMAKE_SOURCE_DIR}/src/fade2d/include
)

configure_file(Bounce.h.in Bounce.h)

file(GLOB src *.cpp *.h)

add_executable(Bounce ${src} ${CMAKE_BINARY_DIR}/src/bounce/Bounce.h)

if( UNIX )
    target_compile_features(Bounce PRIVATE cxx_range_for)
endif()
    
	
add_dependencies(Bounce Fade2D)

target_link_libraries(Bounce Fade2D)
