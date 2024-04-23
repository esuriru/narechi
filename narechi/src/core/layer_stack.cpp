#include "layer_stack.hpp"

#include <algorithm>

namespace narechi
{
    layer_stack::~layer_stack()
    {
        for (layer* layer : layers)
        {
            layer->on_detach();
            delete layer;
        }
    }

    void layer_stack::push_layer(layer* layer)
    {
        // Place it in the back of whatever layer is in front of it
        layers.emplace(layers.begin() + layer_insert_index, layer);
    }

    void layer_stack::push_overlay(layer* overlay)
    {
        // Place it to the back
        layers.emplace_back(overlay);
    }

    void layer_stack::pop_layer(layer* layer)
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

    void layer_stack::pop_overlay(layer* overlay)
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