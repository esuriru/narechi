#include "graphics/image.hpp"

#include "stb_image.h"
#include "core/assert.hpp"

namespace narechi::graphics
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

        return loading_image->data ? loading_image : nullptr;
    }

    sptr<image> image::load_from_memory(
        const uint8_t* data, uint32_t size, const image_load_options& options)
    {
        sptr<image> loading_image = make_sptr<image>();
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        int width, height, channels;
        loading_image->data
            = stbi_load_from_memory(data, size, &width, &height, &channels, 0);
        NRC_ASSERT(
            loading_image->data, "Image could not be loaded from memory");
        loading_image->width = width;
        loading_image->height = height;
        loading_image->channel_count = channels;

        return loading_image->data ? loading_image : nullptr;
    }

    uptr<image> image::load_owned(
        const std::filesystem::path& path, const image_load_options& options)
    {
        uptr<image> loading_image = make_uptr<image>();
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        load(loading_image.get(), path);

        return loading_image->data ? std::move(loading_image) : nullptr;
    }

    uptr<image> image::load_owned_from_memory(
        const uint8_t* data, uint32_t size, const image_load_options& options)
    {
        uptr<image> loading_image = make_uptr<image>();
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        int width, height, channels;
        loading_image->data
            = stbi_load_from_memory(data, size, &width, &height, &channels, 0);
        NRC_ASSERT(
            loading_image->data, "Image could not be loaded from memory");
        loading_image->width = width;
        loading_image->height = height;
        loading_image->channel_count = channels;

        return loading_image->data ? std::move(loading_image) : nullptr;
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
        NRC_ASSERT(
            image->data, "Image could not be loaded at path: ", path.string());
        image->width = width;
        image->height = height;
        image->channel_count = channels;
    }
}