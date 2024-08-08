set(NARECHI_SOURCES
    "src/core/logger.cpp"
    "src/core/app.cpp"
    "src/core/window.cpp"
    "src/core/layer_stack.cpp"

    "src/rendering/renderer_api.cpp"
    "src/rendering/render_command.cpp"
    "src/rendering/framebuffer.cpp"


    "src/platform/win32/win32window.cpp"

    "src/utils/time_utils.cpp"
)

if(${NRC_RENDERER_API} STREQUAL "opengl")
    set(RENDERER_API_SOURCES
        "")
elseif(${NRC_RENDERER_API} STREQUAL "vulkan")
    set(RENDERER_API_SOURCES
        "src/platform/vulkan/vulkan_renderer_api.cpp"
        "src/platform/vulkan/vulkan_shader.cpp"
        "src/platform/vulkan/vulkan_framebuffer.cpp"
    )
else()
    error("Unsupported Renderer API: " ${NRC_RENDERER_API})
endif()

add_library(narechi-engine SHARED ${NARECHI_SOURCES} ${RENDERER_API_SOURCES})

target_link_libraries(narechi-engine PRIVATE glfw)

target_include_directories(narechi-engine PUBLIC "include")

# TODO - Build static or shared setting
target_compile_definitions(narechi-engine PRIVATE
    "NOMINMAX")

if(WIN32)
    target_compile_definitions(narechi-engine PRIVATE 
        "NRC_PLATFORM_WINDOWS"
        "NRC_DEBUG"
        "NRC_BUILD_DLL"
    )
else()

endif()

if(${NRC_RENDERER_API} STREQUAL "opengl")
    target_compile_definitions(narechi-engine PRIVATE 
        "NRC_RENDERER_API_OPENGL")
elseif(${NRC_RENDERER_API} STREQUAL "vulkan")
    target_compile_definitions(narechi-engine PRIVATE 
        "NRC_RENDERER_API_VULKAN")
else()
    error("Unsupported Renderer API: " ${NRC_RENDERER_API})
endif()