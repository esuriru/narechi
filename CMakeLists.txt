cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(narechi LANGUAGES CXX)

set(NARECHI_SOURCES
    "src/entry.cpp"
    "src/core/assert.hpp"
    "src/core/core.hpp"

    "src/core/logger.hpp"
    "src/core/logger.cpp"

    "src/core/app.hpp"
    "src/core/app.cpp"

    "src/utils/time_utils.hpp"
    "src/utils/time_utils.cpp"
)

add_executable(narechi ${NARECHI_SOURCES})

target_include_directories(narechi PUBLIC "src")

if (WIN32)
    target_compile_definitions(narechi PUBLIC "NRC_PLATFORM_WINDOWS;NRC_DEBUG;")
else()
endif()

