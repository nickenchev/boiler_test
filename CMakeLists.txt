cmake_minimum_required(VERSION 3.2)
project(ecsdemo)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

add_executable(ecsdemo
  src/main.cpp
  src/blankpart.cpp)

target_include_directories(ecsdemo PUBLIC
    /Users/nenchev/Developer/projects/boiler/include)
target_link_libraries(ecsdemo /Users/nenchev/Developer/projects/boiler/build/libboiler.a)
