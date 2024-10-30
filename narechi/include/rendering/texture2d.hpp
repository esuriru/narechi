#pragma once

#include "image.hpp"
#include "rendering/texture.hpp"

#include <filesystem>

namespace narechi::rendering
{
    class NRC_API texture2d : public texture
    {
    public:
        static sptr<texture2d> load(const std::filesystem::path& path,
            const rendering::image_load_options& options);
        static sptr<texture2d> load_from_memory(const uint8_t* data,
            uint32_t size, const rendering::image_load_options& options);
    };
}