#pragma once

#include "rendering/renderer_api.hpp"

namespace narechi
{
    class opengl_renderer_api final : public renderer_api
    {
    public:
        virtual void init() override {}
        virtual void cleanup() override {}

        virtual void clear_color(const glm::vec4& color) override;
    };
}