# Cmake for engine library


# Set the minimum version of CMake that can be used

cmake_minimum_required(VERSION 3.14)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set the project name
project(Engine)

# set every file private other than the Engine.h

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Add the library
add_library(Engine STATIC ${SOURCES} ${HEADERS})

# Add the include directory
target_include_directories(Engine PUBLIC "include/")

# Add the raylib library as a dependency
target_link_libraries(Engine raylib)
