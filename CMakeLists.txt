# TODO - Use this video as a reference: 
# https://www.youtube.com/watch?v=ZuHK_5cJ6B8
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(narechi LANGUAGES CXX)

add_subdirectory("narechi")
add_subdirectory("narechi-launcher")

include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip 
    URL_HASH
        SHA256=09C5716296787E1F7FCB87B1CBDBF26814EC1288ED6259CCD30D5D9795809FA5
)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.zip
    URL_HASH
        SHA256=A133DDC3D3C66143EBA9035621DB8E0BCF34DBA1EE9514A9E23E96AFD39FD57A
)

add_subdirectory("deps/glm")
target_link_libraries(narechi-engine PUBLIC glm::glm)

add_subdirectory("deps/glfw")
target_include_directories(narechi-engine PUBLIC ${GLFW_SOURCE_DIR})

find_package(Vulkan)

if(Vulkan_FOUND)
    message(STATUS "Using Vulkan Lib at: " ${Vulkan_LIBRARY})
else()
    message(FATAL_ERROR "Vulkan was not found")
endif()

target_link_libraries(narechi-engine PUBLIC ${Vulkan_LIBRARY})
target_include_directories(narechi-engine PUBLIC ${Vulkan_INCLUDE_DIR})