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

        void add_vertex_buffer(
            sptr<graphics::vertex_buffer> vertex_buffer) override;
        void set_index_buffer(
            sptr<graphics::index_buffer> index_buffer) override;

        sptr<graphics::index_buffer> get_index_buffer() const override;
        const std::vector<sptr<graphics::vertex_buffer>>& get_vertex_buffers()
            const override;

    private:
        sptr<graphics::index_buffer> index_buffer;
        std::vector<sptr<graphics::vertex_buffer>> vertex_buffers;
    };
}