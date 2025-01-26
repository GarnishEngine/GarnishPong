cmake_minimum_required(VERSION 3.22)
project(GarnishPong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    src/*.cc 
)

add_executable(${PROJECT_NAME} main.cc ${SOURCE_FILES})
