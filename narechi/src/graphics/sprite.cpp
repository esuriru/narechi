#include "graphics/sprite.hpp"

namespace narechi::graphics
{
    sptr<sprite> sprite::create(const std::filesystem::path& path,
        const graphics::image_load_options& options)
    {
        sptr<sprite> new_sprite = make_sptr<sprite>();
        new_sprite->texture = texture2d::load(path, options);
        return new_sprite;
    }
}