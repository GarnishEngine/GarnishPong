cmake_minimum_required(VERSION 3.22)
project(GarnishPong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add GarnishEngine
add_subdirectory(3rdParty/GarnishEngine)

# Build GarnishPong
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    src/*.cc 
)

add_executable(GarnishPong main.cc ${SOURCE_FILES})

target_link_libraries(GarnishPong PRIVATE GarnishEngine)

# Include Directories
target_include_directories(GarnishPong PUBLIC
    3rdParty/GarnishEngine/include
    3rdParty/GarnishEngine/3rdParty/SDL/include
)
