# TODO - Use this video as a reference: 
# https://www.youtube.com/watch?v=ZuHK_5cJ6B8
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(NRC_RENDERER_API "opengl")

project(narechi LANGUAGES C CXX)

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

FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.0-docking.zip 
    URL_HASH
        SHA256=657B225D99FD34CE10A3BD0DA2A72359362AE709A774811AA22EE30085660240
)

FetchContent_Declare(
    nativefiledialog-extended
    URL https://github.com/btzy/nativefiledialog-extended/archive/refs/tags/v1.2.1.zip
    URL_HASH
        SHA256=FC359B212E56011931B90BF4241057EDDEC45308BB4D8B9AAB4DFB2F70E3B211
)

FetchContent_Declare(
    yaml-cpp
    URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.zip
    URL_HASH
        SHA256=334E80AB7B52E14C23F94E041C74BAB0742F2281AAD55F66BE2F19F4B7747071
)

FetchContent_Declare(
    flecs
    URL https://github.com/SanderMertens/flecs/archive/refs/tags/v4.0.2.zip
    URL_HASH
        SHA256=AE67CD00BCB5D7665451CF440A87DAE92981765DB683204396622DF10123C018
)

add_subdirectory("deps/glm")
target_link_libraries(narechi-engine PUBLIC glm::glm)

add_subdirectory("deps/glfw")
target_link_libraries(narechi-engine PUBLIC glfw)
target_include_directories(narechi-engine PUBLIC ${GLFW_SOURCE_DIR})

add_subdirectory("deps/imgui")
target_link_libraries(narechi-engine PUBLIC imgui)
target_include_directories(narechi-engine PUBLIC ${NRC_IMGUI_SOURCE_DIR})

add_subdirectory("deps/nativefiledialog-extended")
target_link_libraries(narechi-engine PUBLIC nfd)

add_subdirectory("deps/yaml-cpp")
target_link_libraries(narechi-engine PUBLIC yaml-cpp::yaml-cpp)

add_subdirectory("deps/flecs")
target_link_libraries(narechi-engine PUBLIC flecs::flecs_static)

add_subdirectory("deps/stb")
target_link_libraries(narechi-engine PUBLIC stb)

if(${NRC_RENDERER_API} STREQUAL "vulkan")
    message(STATUS "narechi using Vulkan")
    find_package(Vulkan)

    if(Vulkan_FOUND)
        message(STATUS "Using Vulkan Lib at: " ${Vulkan_LIBRARY})
    else()
        message(FATAL_ERROR "Vulkan was not found")
    endif()

    target_link_libraries(narechi-engine PUBLIC ${Vulkan_LIBRARY})
    target_include_directories(narechi-engine PUBLIC ${Vulkan_INCLUDE_DIR})
elseif(${NRC_RENDERER_API} STREQUAL "opengl")
    message(STATUS "narechi using OpenGL")

    add_subdirectory("deps/glad")
    target_link_libraries(narechi-engine PUBLIC glad)
    target_include_directories(narechi-engine PUBLIC "deps/glad/include")
endif()
