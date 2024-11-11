#pragma once

#include "graphics/texture2d.hpp"
#include "asset/asset.hpp"
#include "yaml-cpp/yaml.h"

NRC_FORWARD_DECL_CLASS(narechi::graphics, sprite)

namespace narechi::asset
{
    class NRC_API sprite_asset : public asset
    {
    public:
        sprite_asset(
            const std::filesystem::path& path, graphics::sprite* owner);

        static sptr<sprite_asset> create(const std::filesystem::path& path);
        static sptr<sprite_asset> load_data(const std::filesystem::path& path);

        sptr<graphics::texture2d> get_texture() const;

    private:
        sptr<graphics::texture2d> texture;
        graphics::sprite* owner;

        void serialize() override;
        void deserialize() override;
    };
}