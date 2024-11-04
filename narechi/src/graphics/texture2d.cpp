#include "graphics/texture2d.hpp"
#include "graphics/renderer_api.hpp"

#include "core/logger.hpp"

// TODO - Macro for vulkan
#include "platform/opengl/opengl_texture2d.hpp"

namespace narechi::graphics
{
    sptr<texture2d> texture2d::load(const std::filesystem::path& path,
        const graphics::image_load_options& options)
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

    sptr<texture2d> texture2d::load_from_memory(const uint8_t* data,
        uint32_t size, const graphics::image_load_options& options)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::vulkan:
#ifdef NRC_RENDERER_API_VULKAN
            return make_sptr<vulkan_texture2d>(data, size, options);
#else
            NRC_CORE_FATAL("Vulkan is not compiled, but selected");
#endif
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_texture2d>(data, size, options);
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