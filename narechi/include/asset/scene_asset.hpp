#pragma once

#include "asset/asset.hpp"
#include "core/core.hpp"

NRC_FORWARD_DECL_CLASS(narechi::scene, scene);

namespace narechi::asset
{
    class scene_asset : public asset
    {
    public:
        scene_asset(const std::filesystem::path& path,
            scene::scene& scene);
    
    private:
        void serialize() override;
        void deserialize() override;

        scene::scene& scene;
    };
}