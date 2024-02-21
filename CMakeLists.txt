cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(narechi LANGUAGES CXX)

set(NARECHI_SOURCES
    "src/entry.cpp"
    "src/core/core.hpp"
    "src/core/logger.hpp"
    "src/core/logger.cpp"
    "src/utils/time_utils.hpp"
    "src/utils/time_utils.cpp"
)

add_executable(narechi ${NARECHI_SOURCES})

target_include_directories(narechi PUBLIC "src")

