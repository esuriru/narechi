cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(narechi LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NARECHI_SOURCES
    "src/entry.cpp"
    "src/core/core.hpp"
    "src/core/logger.hpp"
    "src/utils/time_utils.hpp"
    "src/utils/time_utils.cpp"
)

add_executable(narechi ${NARECHI_SOURCES})

target_include_directories(narechi PUBLIC "src")

