# TODO - Use this video as a reference: 
# https://www.youtube.com/watch?v=ZuHK_5cJ6B8
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(narechi LANGUAGES CXX)

add_subdirectory("narechi")
add_subdirectory("narechi-launcher")

# TODO - Use FetchContent
add_subdirectory("extern/glm")
target_include_directories(narechi-engine PUBLIC "extern")

add_subdirectory("extern/glfw-3.4")
target_include_directories(narechi-engine PUBLIC "extern/glfw-3.4/include")

target_link_libraries(narechi-engine PUBLIC ${Vulkan_LIBRARY})

if (Vulkan_FOUND)
    message("Using Vulkan Lib at: " ${Vulkan_LIBRARY})
endif()

target_link_libraries(narechi-engine PUBLIC ${Vulkan_LIBRARY})
target_include_directories(narechi-engine PUBLIC ${Vulkan_INCLUDE_DIR})

