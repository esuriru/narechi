#pragma once

#include "graphics/image.hpp"
#include "graphics/texture2d.hpp"
#include "graphics/format.hpp"

namespace narechi
{
    class NRC_API opengl_texture2d : public graphics::texture2d
    {
    public:
        opengl_texture2d(const std::filesystem::path& path,
            const graphics::image_load_options& options);
        opengl_texture2d(const uint8_t* data, uint32_t size,
            const graphics::image_load_options& options);
        opengl_texture2d(const uint32_t width, const uint32_t height,
            const graphics::format format);

        void set_min_filter(const filter_mode mode) override;
        void set_mag_filter(const filter_mode mode) override;

        void set_wrap_s(const wrap_mode mode) override;
        void set_wrap_t(const wrap_mode mode) override;

        uint32_t get_width() const override;
        uint32_t get_height() const override;

        void bind(const uint32_t slot) override;
        void unbind() override;

    private:
        uint32_t width;
        uint32_t height;
        graphics::format format;

        uint32_t slot;

        void create_texture_from_image(sptr<graphics::image> image);
    };
}