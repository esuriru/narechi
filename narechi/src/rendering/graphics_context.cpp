#include "rendering/graphics_context.hpp"
#include "rendering/renderer_api.hpp"

#include "core/logger.hpp"
#include "core/app.hpp"

#if defined(NRC_RENDERER_API_VULKAN)
// TODO - vulkan context header
#elif defined(NRC_RENDERER_API_OPENGL)
    #include "platform/opengl/opengl_context.hpp"
#else
    #error "Unsupported renderer API"
#endif

struct GLFWwindow;

namespace narechi
{
    graphics_context::~graphics_context() {}

    uptr<graphics_context> graphics_context::create(app* app)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::none:
            NRC_CORE_FATAL("Renderer API cannot be none");
            break;
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_uptr<opengl_context>(reinterpret_cast<GLFWwindow*>(
                app->get_window().get_native_internal()));
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        case renderer_api::api::vulkan:
#ifdef NRC_RENDERER_API_VULKAN
            // TODO: VulkanContext
            break;
#else
            NRC_CORE_FATAL("Vulkan is not compiled, but selected");
#endif
        }

        return nullptr;
    }
}