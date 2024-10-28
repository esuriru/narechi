#pragma once

#include "core/core.hpp"

#include <filesystem>

namespace narechi::rendering
{
    struct image_load_options
    {
        bool flip_vertically = true;
    };

    // TODO - Store formats inside of image
    class image
    {
    public:
        image();
        ~image();

        static sptr<image> load(const std::filesystem::path& path,
            const image_load_options& image_load_options);
        static uptr<image> load_owned(const std::filesystem::path& path,
            const image_load_options& image_load_options);

        uint8_t* get_data() const;
        uint32_t get_width() const;
        uint32_t get_height() const;
        uint32_t get_channel_count() const;

    private:
        uint8_t* data;
        uint32_t width, height, channel_count;

        static void load(image* image, const std::filesystem::path& path);
    };
}