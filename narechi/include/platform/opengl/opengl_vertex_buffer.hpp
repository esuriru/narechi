#pragma once

#include "graphics/vertex_buffer.hpp"

namespace narechi
{
    class NRC_API opengl_vertex_buffer : public graphics::vertex_buffer
    {
    public:
        opengl_vertex_buffer(const float* vertices, const uint32_t size);

        ~opengl_vertex_buffer();

        void bind() override;
        void unbind() override;
    };
}