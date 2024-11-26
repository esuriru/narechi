#pragma once

#include "core/core.hpp"

#include "flecs.h"

#include <filesystem>

NRC_FORWARD_DECL_CLASS(narechi::asset, scene_asset);

namespace narechi::scene
{
    class NRC_API scene
    {
    public:
        struct scene_data
        {
            std::string name;
            flecs::world world;
        };

        scene();
        scene(const std::filesystem::path& path);
        ~scene();

        static sptr<scene> create(
            const std::filesystem::path& path, const std::string& name);
        static sptr<scene> load(const std::filesystem::path& path);
        static sptr<scene> load(uptr<asset::scene_asset> scene_asset);

        void awake();
        void update(float delta_time);

        void add_entity();

        void save();
        void export_to_dir(
            const std::filesystem::path& dir, bool save = true);

        std::string get_name() const;

    private:
        friend class asset::scene_asset;

        uptr<scene_data> data;
        uptr<asset::scene_asset> asset;
    };
}