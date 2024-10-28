#pragma once

#include "rendering/image.hpp"
#include "rendering/texture2d.hpp"

namespace narechi
{
    class NRC_API opengl_texture2d : public rendering::texture2d
    {
    public:
        opengl_texture2d(const std::filesystem::path& path);

        uint32_t get_width() const override;
        uint32_t get_height() const override;
        uint32_t get_gfx_ctx_id() const override;

    private:
        uptr<rendering::image> image;
        uint32_t gfx_ctx_id;

        void load_image(const std::filesystem::path& path);
        void create_texture();
    };
}