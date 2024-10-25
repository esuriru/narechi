#include "scene/scene.hpp"

#include "asset/scene_asset.hpp"
#include "flecs/addons/cpp/world.hpp"

namespace narechi::scene
{
    scene::scene()
        : data(nullptr)
        , asset(nullptr)
    {
    }

    scene::scene(const std::filesystem::path& path)
        : data(make_uptr<scene::scene_data>())
        , asset(make_uptr<asset::scene_asset>(path, data.get()))
    {
        asset->write();
    }

    scene::~scene()
    {
        asset.reset();
        data->world.release();
    }

    sptr<scene> scene::create(
        const std::filesystem::path& path, const std::string& name)
    {
        sptr<scene> new_scene = make_sptr<scene>(path);
        new_scene->data->name = name;
        new_scene->save();
        return new_scene;
    }

    sptr<scene> scene::load(const std::filesystem::path& path)
    {
        sptr<scene> existing_scene = make_sptr<scene>(path);
        existing_scene->asset->load();
        return existing_scene;
    }

    sptr<scene> scene::load(uptr<asset::scene_asset> scene_asset)
    {
        sptr<scene> existing_scene = make_sptr<scene>();
        existing_scene->asset = std::move(scene_asset);
        existing_scene->asset->to_owned(existing_scene->data);
        return existing_scene;
    }

    void scene::awake()
    {
        flecs::entity test_entity = data->world.entity();
        test_entity.add(flecs::Disabled);
    }

    void scene::update(float delta_time)
    {
        data->world.progress(delta_time);
    }

    void scene::add_entity()
    {
        data->world.entity();
    }

    void scene::save()
    {
        asset->write();
    }

    std::string scene::get_name() const
    {
        return data->name;
    }
}