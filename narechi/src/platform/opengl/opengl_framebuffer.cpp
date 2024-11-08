#include "platform/opengl/opengl_framebuffer.hpp"

#include "core/assert.hpp"
#include "glad/gl.h"

#include "glm/gtc/type_ptr.hpp"

namespace narechi
{
    opengl_framebuffer::opengl_framebuffer(
        const graphics::framebuffer_specification& spec)
        : graphics::framebuffer(spec)
    {
        invalidate();
    }

    opengl_framebuffer::~opengl_framebuffer()
    {
        glDeleteFramebuffers(1, &id);
    }

    void opengl_framebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        glViewport(0, 0, spec.width, spec.height);
    }

    void opengl_framebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void opengl_framebuffer::resize(uint32_t width, uint32_t height)
    {
        spec.width = width;
        spec.height = height;

        invalidate();
    }

    void opengl_framebuffer::clear_color(const glm::vec4& color)
    {
        glClearNamedFramebufferfv(id, GL_COLOR, 0, glm::value_ptr(color));
    }

    void opengl_framebuffer::clear_depth(const float depth)
    {
        glClearNamedFramebufferfv(id, GL_DEPTH, 0, &depth);
    }

    sptr<graphics::texture> opengl_framebuffer::get_color_attachment()
    {
        return color_attachment;
    }

    sptr<graphics::texture> opengl_framebuffer::get_depth_attachment()
    {
        return depth_attachment;
    }

    void opengl_framebuffer::invalidate()
    {
        using namespace graphics;

        // If there is an existing framebuffer object, clean it up
        if (id > 0)
        {
            glDeleteFramebuffers(1, &id);
            color_attachment.reset();
            depth_attachment.reset();
        }

        glCreateFramebuffers(1, &id);

        color_attachment = make_sptr<opengl_texture2d>(
            spec.width, spec.height, format::rgba8);
        color_attachment->set_mag_filter(texture::filter_mode::linear);
        color_attachment->set_min_filter(texture::filter_mode::linear);

        depth_attachment = make_sptr<opengl_texture2d>(
            spec.width, spec.height, format::d24_s8);
        depth_attachment->set_mag_filter(texture::filter_mode::linear);
        depth_attachment->set_min_filter(texture::filter_mode::linear);

        glNamedFramebufferTexture(
            id, GL_COLOR_ATTACHMENT0, color_attachment->get_id(), 0);
        glNamedFramebufferTexture(
            id, GL_DEPTH_ATTACHMENT, depth_attachment->get_id(), 0);

        NRC_ASSERT(glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER)
                == GL_FRAMEBUFFER_COMPLETE,
            "Could not create opengl framebuffer, status: ",
            glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER));
    }
}