#include "platform/opengl/opengl_texture2d.hpp"

#include "core/assert.hpp"

#include "glad/gl.h"

namespace narechi
{
    opengl_texture2d::opengl_texture2d(const std::filesystem::path& path,
        const rendering::image_load_options& options)
        : texture2d()
    {
        load_image(path, options);
        create_texture();
    }

    opengl_texture2d::opengl_texture2d(const uint8_t* data, uint32_t size,
        const rendering::image_load_options& options)
        : texture2d()
    {
        image = rendering::image::load_owned_from_memory(data, size, options);
        NRC_ASSERT(image, "Image not loaded when creating opengl_texture2d");
        create_texture();
    }

    uint32_t opengl_texture2d::get_width() const
    {
        return image->get_width();
    }

    uint32_t opengl_texture2d::get_height() const
    {
        return image->get_height();
    }

    uint32_t opengl_texture2d::get_gfx_ctx_id() const
    {
        return gfx_ctx_id;
    }

    void opengl_texture2d::load_image(const std::filesystem::path& path,
        const rendering::image_load_options& options)
    {
        image = rendering::image::load_owned(path, options);
        NRC_ASSERT(image, "Image not loaded when creating opengl_texture2d");
    }

    void opengl_texture2d::create_texture()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &gfx_ctx_id);
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

        glTextureStorage2D(gfx_ctx_id,
            1,
            internal_format,
            static_cast<GLint>(image->get_width()),
            static_cast<GLint>(image->get_height()));

        glTextureParameteri(gfx_ctx_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gfx_ctx_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(gfx_ctx_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gfx_ctx_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(gfx_ctx_id,
            0,
            0,
            0,
            image->get_width(),
            image->get_height(),
            data_format,
            GL_UNSIGNED_BYTE,
            image->get_data());

        glGenerateTextureMipmap(gfx_ctx_id);
    }

}