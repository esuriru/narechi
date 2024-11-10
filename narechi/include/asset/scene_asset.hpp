#pragma once

#include "asset/asset.hpp"
#include "core/core.hpp"

#include "scene/scene.hpp"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace narechi::asset
{
    class NRC_API scene_asset : public asset
    {
    public:
        scene_asset(const std::filesystem::path& path,
            scene::scene::scene_data* scene_data);
        ~scene_asset();

        static uptr<scene_asset> load_data(const std::filesystem::path& path);

        const scene::scene::scene_data& get_scene_data() const;

        void to_owned(uptr<scene::scene::scene_data>& scene_data);

    private:
        scene::scene::scene_data* scene_data;

        void serialize() override;
        void deserialize() override;
    };
}