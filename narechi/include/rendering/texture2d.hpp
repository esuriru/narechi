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
    };
}