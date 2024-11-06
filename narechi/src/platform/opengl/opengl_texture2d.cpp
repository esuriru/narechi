#include "platform/opengl/opengl_texture2d.hpp"

#include "core/assert.hpp"

#include "glad/gl.h"

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

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

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