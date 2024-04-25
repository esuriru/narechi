set(NARECHI_SOURCES
    "src/core/logger.cpp"
    "src/core/app.cpp"
    "src/core/window.cpp"
    "src/core/layer_stack.cpp"

    "src/rendering/renderer_api.cpp"
    "src/rendering/render_command.cpp"

    "src/platform/vulkan/vulkan_renderer_api.cpp"

    "src/platform/win32/win32window.cpp"

    "src/utils/time_utils.cpp"
)

add_library(narechi-engine SHARED ${NARECHI_SOURCES})

target_link_libraries(narechi-engine PRIVATE glfw)

target_include_directories(narechi-engine PUBLIC "include")

if (WIN32)
    target_compile_definitions(narechi-engine PRIVATE 
        "NRC_PLATFORM_WINDOWS;NRC_DEBUG;NRC_BUILD_DLL;NOMINMAX")
else()
endif()