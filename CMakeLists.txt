cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(narechi LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(narechi "src/entry.cpp")
