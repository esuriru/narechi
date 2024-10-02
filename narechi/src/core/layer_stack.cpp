#include "core/layer_stack.hpp"

#include <algorithm>

namespace narechi
{
    void layer_stack::push_layer(sptr<layer> layer)
    {
        // Place it in the back of whatever layer is in front of it
        layers.emplace(layers.begin() + layer_insert_index, layer);
        layer->on_attach();
        layer_insert_index++;
    }

    void layer_stack::push_overlay(sptr<layer> overlay)
    {
        // Place it to the back
        layers.emplace_back(overlay);
        overlay->on_attach();
    }

    void layer_stack::pop_layer(sptr<layer> layer)
    {
        auto it = std::find(
            layers.begin(), layers.begin() + layer_insert_index, layer);
        if (it != layers.begin() + layer_insert_index)
        {
            // Call on_detach, remove from the stack,
            // and reset the layer insert index
            layer->on_detach();
            layers.erase(it);
            layer_insert_index--;
        }
    }

    void layer_stack::pop_overlay(sptr<layer> overlay)
    {
        auto it = std::find(
            layers.begin() + layer_insert_index, layers.end(), overlay);
        if (it != layers.end())
        {
            // Call on_detach, remove from the stack
            overlay->on_detach();
            layers.erase(it);
        }
    }
}