#include "rendering/texture2d.hpp"
#include "rendering/renderer_api.hpp"
#include "core/logger.hpp"

#include "platform/opengl/opengl_texture2d.hpp"

namespace narechi::rendering
{
    sptr<texture2d> texture2d::load(const std::filesystem::path& path,
        const rendering::image_load_options& options)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::vulkan:
#ifdef NRC_RENDERER_API_VULKAN
            return make_sptr<vulkan_texture2d>(path, options);
#else
            NRC_CORE_FATAL("Vulkan is not compiled, but selected");
#endif
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_texture2d>(path, options);
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        default:
            break;
        }

        NRC_CORE_ERROR("No `texture2d` available for selected Renderer API");
        return nullptr;
    }
}