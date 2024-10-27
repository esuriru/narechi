#pragma once

#include "core/core.hpp"

#include <filesystem>

namespace narechi::rendering
{
    class image
    {
    public:
        image() = default;
        ~image();

        static sptr<image> load(
            const std::filesystem::path& path, bool flip_vertically = true);
        
        uint8_t* get_data() const;
        int get_width() const;
        int get_height() const;

    private:
        uint8_t* data;
        int width, height;
    };
}