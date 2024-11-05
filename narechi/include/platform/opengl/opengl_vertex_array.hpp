#pragma once

#include "graphics/vertex_array.hpp"

namespace narechi
{
    class opengl_vertex_array : public graphics::vertex_array
    {
    public:
        opengl_vertex_array();
        ~opengl_vertex_array();

        void bind() override;
        void unbind() override;
    
    private:
        uint32_t id;
    };
}