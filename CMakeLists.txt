cmake_minimum_required(VERSION 3.19)
project(project_defend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(project_defend main.cpp)
target_compile_options(project_defend PRIVATE -Wall; -O2)
add_custom_command(TARGET project_defend POST_BUILD COMMAND strip $<TARGET_FILE:project_defend>)