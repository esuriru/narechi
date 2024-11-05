#pragma once

#include "core/core.hpp"

#include "graphics/index_buffer.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/handle.hpp"

#include <vector>

namespace narechi::graphics
{
    class vertex_array : public handle
    {
    public:
        virtual ~vertex_array() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void add_vertex_buffer(sptr<vertex_buffer> vertex_buffer) = 0;
        virtual void set_index_buffer(sptr<index_buffer> index_buffer) = 0;

        virtual sptr<index_buffer> get_index_buffer() const = 0;
        virtual const std::vector<sptr<vertex_buffer>>& get_vertex_buffers()
            const
            = 0;

        static sptr<vertex_array> create();
    };
}