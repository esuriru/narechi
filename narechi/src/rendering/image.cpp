#include "rendering/image.hpp"

#include "stb_image.h"
#include "core/assert.hpp"

namespace narechi::rendering
{
    image::image()
        : data(nullptr)
    {
    }

    image::~image()
    {
        stbi_image_free(data);
    }

    sptr<image> image::load(
        const std::filesystem::path& path, const image_load_options& options)
    {
        sptr<image> loading_image = make_sptr<image>();
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        load(loading_image.get(), path);

        return loading_image;
    }

    uptr<image> image::load_owned(
        const std::filesystem::path& path, const image_load_options& options)
    {
        uptr<image> loading_image = make_uptr<image>();
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        load(loading_image.get(), path);

        return std::move(loading_image);
    }

    uint8_t* image::get_data() const
    {
        return data;
    }

    uint32_t image::get_width() const
    {
        return width;
    }

    uint32_t image::get_height() const
    {
        return height;
    }

    uint32_t image::get_channel_count() const
    {
        return channel_count;
    }

    void image::load(image* image, const std::filesystem::path& path)
    {
        int width, height, channels;
        image->data
            = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
        NRC_ASSERT(image->data, "Image not loaded at path: ", path.string());
        image->width = width;
        image->height = height;
        image->channel_count = channels;
    }
}