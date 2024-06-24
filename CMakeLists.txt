cmake_minimum_required(VERSION 3.29)
project(smallbluestar C)

set(CMAKE_C_STANDARD 11)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)

#include_directories("/opt/homebrew/Cellar/raylib/5.0/include")
add_executable(smallbluestar src/main.c
        src/map.c
        src/map.h
        src/physics.c
        src/bsutils.c
        src/bsutils.h
        src/physics.h
        src/inputhandle.c
        src/inputhandle.h
        src/inputhandle.c
        src/animation.c
        src/animation.h
)

target_link_libraries(smallbluestar raylib tmx raylib-tmx)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()