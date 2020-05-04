cmake_minimum_required(VERSION 3.11) # Need 3.11+ for FetchContent 
project(draw_game) # Name of Executable

# Minimum version of Raylib to support
find_package(raylib 3.0 REQUIRED) # Let CMake search for a raylib-config.cmake && raylib REQUIRED

# This is the main part:
add_executable(${PROJECT_NAME} ../../main.c)
#set(raylib_VERBOSE 1) #debugging
target_link_libraries(${PROJECT_NAME} raylib)

