cmake_minimum_required(VERSION 3.22)
project(SDL_GameOfLife C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(SDL_GameOfLife main.c )
target_link_libraries(SDL_GameOfLife ${SDL2_LIBRARIES})

