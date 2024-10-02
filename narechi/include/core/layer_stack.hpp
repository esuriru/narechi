#pragma once

#include "core/core.hpp"
#include "core/layer.hpp"

#include <cstdint>
#include <vector>

namespace narechi
{
    class NRC_API layer_stack final
    {
    public:
        layer_stack() = default;

        void push_layer(sptr<layer> layer);
        void push_overlay(sptr<layer> overlay);

        void pop_layer(sptr<layer> layer);
        void pop_overlay(sptr<layer> overlay);

        inline std::vector<sptr<layer>>::iterator begin()
        {
            return layers.begin();
        }

        inline std::vector<sptr<layer>>::iterator end()
        {
            return layers.end();
        }

        inline std::vector<sptr<layer>>::reverse_iterator rbegin()
        {
            return layers.rbegin();
        }

        inline std::vector<sptr<layer>>::reverse_iterator rend()
        {
            return layers.rend();
        }

        inline std::vector<sptr<layer>>::const_iterator begin() const
        {
            return layers.begin();
        }

        inline std::vector<sptr<layer>>::const_iterator end() const
        {
            return layers.end();
        }

        inline std::vector<sptr<layer>>::const_reverse_iterator rbegin() const
        {
            return layers.rbegin();
        }

        inline std::vector<sptr<layer>>::const_reverse_iterator rend() const
        {
            return layers.rend();
        }

    private:
        std::vector<sptr<layer>> layers;
        uint32_t layer_insert_index = 0;
    };
}