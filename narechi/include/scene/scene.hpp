#pragma once

#include "asset/component_def_asset.hpp"
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
        static sptr<scene> load(const std::filesystem::path& path,
            sptr<asset::component_def_asset> cdef);
        static sptr<scene> load(uptr<asset::scene_asset> scene_asset,
            sptr<asset::component_def_asset> cdef);

        void awake();
        void update(float delta_time);

        void add_entity(const std::string& name);
        void add_empty_sprite(const std::string& name);

        void save();
        void export_to_dir(const std::filesystem::path& dir,
            sptr<asset::component_def_asset> cdef_asset, bool save = true);

        std::string get_name() const;
        flecs::world get_world() const;

    private:
        friend class asset::scene_asset;

        uptr<scene_data> data;
        uptr<asset::scene_asset> asset;
    };
}