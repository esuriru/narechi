#include "rendering/image.hpp"

#include "stb_image.h"

namespace narechi::rendering
{
    image::~image()
    {
        stbi_image_free(data);
    }

    sptr<image> image::load(
        const std::filesystem::path& path, bool flip_vertically)
    {
        sptr<image> loading_image = make_sptr<image>();
        stbi_set_flip_vertically_on_load(flip_vertically);
        loading_image->data = stbi_load(path.string().c_str(),
            &loading_image->width,
            &loading_image->height,
            nullptr,
            4);

        return loading_image;
    }

    uint8_t* image::get_data() const
    {
        return data;
    }

    int image::get_width() const
    {
        return width;
    }

    int image::get_height() const
    {
        return height;
    }
}