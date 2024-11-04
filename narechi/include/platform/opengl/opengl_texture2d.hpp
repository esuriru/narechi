#pragma once

#include "graphics/image.hpp"
#include "graphics/texture2d.hpp"

namespace narechi
{
    class NRC_API opengl_texture2d : public graphics::texture2d
    {
    public:
        opengl_texture2d(const std::filesystem::path& path,
            const graphics::image_load_options& options);
        opengl_texture2d(const uint8_t* data, uint32_t size,
            const graphics::image_load_options& options);

        uint32_t get_width() const override;
        uint32_t get_height() const override;
        uint32_t get_gfx_ctx_id() const override;

    private:
        uptr<graphics::image> image;
        uint32_t gfx_ctx_id;

        void load_image(const std::filesystem::path& path,
            const graphics::image_load_options& options);
        void create_texture();
    };
}