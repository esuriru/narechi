#pragma once

#include "core/core.hpp"

#include "graphics/handle.hpp"
#include "graphics/buffer_element.hpp"

#include <vector>

namespace narechi::graphics
{
    class vertex_buffer : public handle
    {
    public:
        class buffer_layout
        {
        public:
            buffer_layout() = default;
            buffer_layout(
                std::initializer_list<graphics::buffer_element> elements);

            uint32_t get_stride() const;
            const std::vector<graphics::buffer_element>& get_elements() const;

        private:
            std::vector<graphics::buffer_element> elements;
            uint32_t stride;

            void invalidate();
        };

        virtual ~vertex_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        const buffer_layout& get_layout() const;
        void set_layout(const buffer_layout& layout);

        static sptr<vertex_buffer> create(
            const float* vertices, const uint32_t size);

    private:
        buffer_layout layout {};
    };
}