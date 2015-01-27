cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(Bounce)

# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Executables."
   )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(GLEW REQUIRED)

add_subdirectory(dep)
add_subdirectory(src)
