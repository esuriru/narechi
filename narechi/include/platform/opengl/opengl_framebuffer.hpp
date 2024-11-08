#pragma once

#include "graphics/framebuffer.hpp"
#include "platform/opengl/opengl_texture2d.hpp"

namespace narechi
{
    class opengl_framebuffer : public graphics::framebuffer
    {
    public:
        opengl_framebuffer(const graphics::framebuffer_specification& spec);
        ~opengl_framebuffer();

        void bind() override;
        void unbind() override;

        void resize(uint32_t width, uint32_t height) override;

        void clear_color(const glm::vec4& color) override;
        void clear_depth(const float depth) override;

        sptr<graphics::texture> get_color_attachment() override;
        sptr<graphics::texture> get_depth_attachment() override;

    private:
        sptr<opengl_texture2d> color_attachment;
        sptr<opengl_texture2d> depth_attachment;

        void invalidate();
    };
}