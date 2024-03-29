
# Add the include directory
# target_include_directories(Engine PUBLIC "include/" PUBLIC "vendor/entt/single_include/" PRIVATE "src/")
# project internal include directory for the engine
# it is not recommended to use this for the game


# Cmake for engine library
# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.14)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set the project name
project(Engine)

# include everything in the src directory for internal use
include_directories(src)

# Add the source files
file(GLOB_RECURSE SRC_SOURCES "src/*.cpp")
file(GLOB_RECURSE SRC_HEADERS "src/*.h")
file(GLOB_RECURSE VENDOR_INCLUDE "vendor/entt/single_include/**/*.*" )

# Add the library
add_library(Engine STATIC "include/" ${SRC_SOURCES} ${SRC_HEADERS}
        src/ECS/Entity.cpp
        src/ECS/Entity.h
        src/ECS/Components.h
        src/ECS/PhysicsBody.h
        src/ECS/Rotation.h
        src/ECS/Transform.h
        src/ECS/BoxRenderer.h
)


#target_include_directories(Engine PUBLIC include/ ${VENDOR_INCLUDE} ${SRC_HEADERS} PRIVATE ${SRC_SOURCES} )

target_include_directories(Engine PUBLIC "include/" PUBLIC "vendor/entt/single_include/" PUBLIC "src/")
# Add the raylib library as a dependency
target_link_libraries(Engine raylib)
