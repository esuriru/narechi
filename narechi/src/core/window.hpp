#pragma once

#include "core.hpp"

#include <string>
#include <cstdint>

namespace narechi
{
    // properties for window creation and management
    struct window_properties
    {
        std::string title;
        uint32_t width, height;
    };

    // base class for desktop window
    class window
    {
    public:
        virtual ~window() = default;
    
        static uptr<window> create(
            const window_properties& properties = window_properties());
        
        virtual void* get_native_internal() const = 0;
        
        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;
    };
}