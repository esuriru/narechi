cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(narechi LANGUAGES CXX)

set(NARECHI_SOURCES
    "narechi/src/entry.cpp"
    "narechi/src/core/assert.hpp"
    "narechi/src/core/core.hpp"

    "narechi/src/core/logger.hpp"
    "narechi/src/core/logger.cpp"

    "narechi/src/core/app.hpp"
    "narechi/src/core/app.cpp"

    "narechi/src/utils/time_utils.hpp"
    "narechi/src/utils/time_utils.cpp"
)

add_executable(narechi ${NARECHI_SOURCES})

target_include_directories(narechi PUBLIC "narechi/src")

if (WIN32)
    target_compile_definitions(narechi PUBLIC "NRC_PLATFORM_WINDOWS;NRC_DEBUG;")
else()
endif()

