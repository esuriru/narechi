#pragma once

#include "graphics/index_buffer.hpp"

namespace narechi
{
    class opengl_index_buffer : public graphics::index_buffer
    {
    public:
        opengl_index_buffer(const uint32_t* indices, const uint32_t count);
        ~opengl_index_buffer();

        void bind() override;
        void unbind() override;
    };
}