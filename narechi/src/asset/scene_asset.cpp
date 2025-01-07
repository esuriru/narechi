#include "asset/scene_asset.hpp"

#include "flecs/addons/cpp/mixins/json/decl.hpp"
#include "yaml-cpp/yaml.h"
#include "scene/component.hpp"

namespace narechi::asset
{
    scene_asset::scene_asset(
        const std::filesystem::path& path, scene::scene::scene_data* scene_data)
        : asset(path)
        , scene_data(scene_data)
    {
    }

    scene_asset::~scene_asset()
    {
        if (is_owning)
        {
            delete scene_data;
        }
    }

    uptr<scene_asset> scene_asset::load_data(const std::filesystem::path& path)
    {
        uptr<scene_asset> asset
            = make_uptr<scene_asset>(path, new scene::scene::scene_data());
        asset->is_owning = true;
        asset->load();
        return std::move(asset);
    }

    const scene::scene::scene_data& scene_asset::get_scene_data() const
    {
        return *scene_data;
    }

    void scene_asset::to_owned(uptr<scene::scene::scene_data>& scene_data)
    {
        is_owning = false;
        scene_data.reset(this->scene_data);
    }

    void scene_asset::serialize()
    {
        if (node.IsNull())
        {
            node = YAML::Node(YAML::NodeType::Map);
            node.force_insert("Name", scene_data->name);
            node.force_insert(
                "World Data", scene_data->world.to_json().c_str());
        }
        else
        {
            node["Name"] = scene_data->name;
            node["World Data"] = scene_data->world.to_json().c_str();
        }
    }

    void scene_asset::deserialize()
    {
        if (!node.IsMap())
        {
            return;
        }

        if (is_owning)
        {
            // Don't load the world
            scene_data->name = node["Name"].as<std::string>();
        }
        else
        {
            scene_data->name = node["Name"].as<std::string>();
            scene_data->world.from_json(
                node["World Data"].as<std::string>().c_str());
        }
    }
}