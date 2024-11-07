#pragma once

#include "graphics/renderer_api.hpp"
#include "graphics/vertex_array.hpp"

namespace narechi
{
    class opengl_renderer_api final : public graphics::renderer_api
    {
    public:
        void init() override;
        void cleanup() override
        {
        }

        void clear_color(const glm::vec4& color) override;
        void draw_indexed(std::shared_ptr<graphics::vertex_array> vertex_array,
            uint32_t index_count = 0) override;
    };
}