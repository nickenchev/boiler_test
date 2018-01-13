cmake_minimum_required(VERSION 3.2)
project(ecsdemo)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(/home/nenchev/Developer/projects/boiler/CMakeLists.txt)

add_executable(ecsdemo
  src/main.cpp
  src/blankpart.cpp)

include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(ecsdemo ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${ZLIB_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} boiler)
