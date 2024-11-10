#pragma once

#include "asset/asset.hpp"
#include "yaml-cpp/yaml.h"

NRC_FORWARD_DECL_CLASS(narechi::graphics, sprite)

namespace narechi::asset
{
    class sprite_asset : public asset
    {
    public:
        sprite_asset(
            const std::filesystem::path& path, graphics::sprite* owner);

    private:
        // YAML::Node node;
        graphics::sprite* owner;

        void serialize() override;
        void deserialize() override;
    };
}