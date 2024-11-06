#include "platform/opengl/opengl_texture2d.hpp"
#include "platform/opengl/opengl_utils.hpp"

#include "core/assert.hpp"

#include "glad/gl.h"

namespace
{
    constexpr GLenum filter_mode_to_opengl_filter_mode(
        const narechi::graphics::texture::filter_mode mode)
    {
        switch (mode)
        {
        case narechi::graphics::texture::filter_mode::linear:
            return GL_LINEAR;
        case narechi::graphics::texture::filter_mode::nearest:
            return GL_NEAREST;
        default:
            break;
        }

        NRC_CORE_ERROR("Could not convert filter mode to opengl filter mode");
    }

    constexpr GLenum wrap_mode_to_opengl_wrap_mode(
        const narechi::graphics::texture::wrap_mode mode)
    {
        switch (mode)
        {
        case narechi::graphics::texture::wrap_mode::repeat:
            return GL_REPEAT;
        case narechi::graphics::texture::wrap_mode::clamp_edge:
            return GL_CLAMP_TO_EDGE;
        case narechi::graphics::texture::wrap_mode::clamp_border:
            return GL_CLAMP_TO_BORDER;
        default:
            break;
        }

        NRC_CORE_ERROR("Could not convert wrap mode to opengl wrap mode");
    }
}

namespace narechi
{
    opengl_texture2d::opengl_texture2d(const std::filesystem::path& path,
        const graphics::image_load_options& options)
        : texture2d()
    {
        sptr<graphics::image> image = graphics::image::load(path, options);
        NRC_ASSERT(image, "Image not loaded when creating opengl_texture2d");
        create_texture_from_image(image);
    }

    opengl_texture2d::opengl_texture2d(const uint8_t* data, uint32_t size,
        const graphics::image_load_options& options)
        : texture2d()
    {
        sptr<graphics::image> image
            = graphics::image::load_from_memory(data, size, options);
        NRC_ASSERT(image, "Image not loaded when creating opengl_texture2d");
        create_texture_from_image(image);
    }

    opengl_texture2d::opengl_texture2d(const uint32_t width,
        const uint32_t height, const graphics::format format)
        : width(width)
        , height(height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id,
            1,
            utils::format_to_opengl_format(format),
            static_cast<GLint>(width),
            static_cast<GLint>(height));
    }

    void opengl_texture2d::set_min_filter(const filter_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_MIN_FILTER, filter_mode_to_opengl_filter_mode(mode));
    }

    void opengl_texture2d::set_mag_filter(const filter_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_MAG_FILTER, filter_mode_to_opengl_filter_mode(mode));
    }

    void opengl_texture2d::set_wrap_s(const wrap_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_WRAP_S, wrap_mode_to_opengl_wrap_mode(mode));
    }

    void opengl_texture2d::set_wrap_t(const wrap_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_WRAP_T, wrap_mode_to_opengl_wrap_mode(mode));
    }

    uint32_t opengl_texture2d::get_width() const
    {
        return width;
    }

    uint32_t opengl_texture2d::get_height() const
    {
        return height;
    }

    void opengl_texture2d::create_texture_from_image(
        sptr<graphics::image> image)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        GLenum internal_format, data_format;
        if (image->get_channel_count() == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
        }
        else if (image->get_channel_count() == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
        }

        glTextureStorage2D(id,
            1,
            internal_format,
            static_cast<GLint>(image->get_width()),
            static_cast<GLint>(image->get_height()));

        set_min_filter(filter_mode::linear);
        set_mag_filter(filter_mode::nearest);

        set_wrap_s(wrap_mode::repeat);
        set_wrap_t(wrap_mode::repeat);

        glTextureSubImage2D(id,
            0,
            0,
            0,
            image->get_width(),
            image->get_height(),
            data_format,
            GL_UNSIGNED_BYTE,
            image->get_data());

        glGenerateTextureMipmap(id);

        width = image->get_width();
        height = image->get_height();
    }

}