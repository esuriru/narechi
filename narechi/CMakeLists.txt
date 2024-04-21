set(NARECHI_SOURCES
    "src/entry.hpp"
    "src/narechi.hpp"

    "src/core/events/event.hpp"
    "src/core/events/app_event.hpp"

    "src/core/assert.hpp"
    "src/core/core.hpp"

    "src/core/logger.hpp"
    "src/core/logger.cpp"

    "src/core/app.hpp"
    "src/core/app.cpp"

    "src/core/window.hpp"
    "src/core/window.cpp"

    "src/core/layer.hpp"
    "src/core/layer_stack.hpp"
    "src/core/layer_stack.cpp"

    "src/core/buffer.hpp"

    "src/rendering/buffer.hpp"
    "src/rendering/shader_type.hpp"
    "src/rendering/renderer_api.hpp"
    "src/rendering/renderer_api.cpp"

    "src/rendering/render_command.hpp"
    "src/rendering/render_command.cpp"

    "src/platform/vulkan/vulkan_renderer_api.hpp"
    "src/platform/vulkan/vulkan_renderer_api.cpp"

    "src/platform/win32/win32window.hpp"
    "src/platform/win32/win32window.cpp"

    "src/utils/time_utils.hpp"
    "src/utils/time_utils.cpp"
)

add_library(narechi-engine SHARED ${NARECHI_SOURCES})

target_link_libraries(narechi-engine PRIVATE glfw)

target_include_directories(narechi-engine PUBLIC "src")

if (WIN32)
    target_compile_definitions(narechi-engine PRIVATE 
        "NRC_PLATFORM_WINDOWS;NRC_DEBUG;NRC_BUILD_DLL;")
else()
endif()