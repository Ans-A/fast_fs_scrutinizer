cmake_minimum_required(VERSION 3.14)

project(FastFSScrutinizer VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(fast_fs_scrutinizer src/main.cpp)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "CMAKE_CXX_COMPILER (auto-detected): ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID detected by CMake: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version detected by CMake: ${CMAKE_CXX_COMPILER_VERSION}")
