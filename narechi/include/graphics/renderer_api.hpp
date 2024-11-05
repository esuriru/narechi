#pragma once

#include "glm/glm.hpp" // IWYU pragma: keep (glm::vec4)

#include "core/core.hpp"

#include "graphics/vertex_array.hpp"

namespace narechi::graphics
{
    class renderer_api
    {
    public:
        enum class api
        {
            none = 0,
            opengl,
            vulkan
        };

        virtual ~renderer_api() = default;

        virtual void init() = 0;
        virtual void cleanup() = 0;

        virtual void clear_color(const glm::vec4& color) = 0;
        virtual void draw_indexed(
            std::shared_ptr<graphics::vertex_array> vertex_array,
            uint32_t index_count = 0)
            = 0;

        static uptr<renderer_api> create();

        static api get_api();
    private:
        static api api_type;
    };
}