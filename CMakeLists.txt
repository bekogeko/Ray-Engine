cmake_minimum_required(VERSION 3.14) # FetchContent is available in 3.11+
# c++ standard 17
set(CMAKE_CXX_STANDARD 17)
project(Game)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()



# Add the executable, link the raylib library

add_executable(${PROJECT_NAME} Game/main.cpp
        Game/Player.cpp
        Game/Player.h
        Game/Obstacle.cpp
        Game/Obstacle.h
)


# Engine Project
add_subdirectory(Engine)

# link the engine library
target_link_libraries(${PROJECT_NAME} Engine)
#add_dependencies(${PROJECT_NAME} Engine)

# include the engine headers with the "Engine/" prefix
#target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE Engine)


#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
#add_dependencies(${PROJECT_NAME} Engine)
# add prefix to the engine link
# for example "Engine/Debug.h"




## Web Configurations
#if (${PLATFORM} STREQUAL "Web")
#    # Tell Emscripten to build an example.html file.
#    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
#endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()