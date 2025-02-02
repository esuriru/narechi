#include "panels/inspector_panel.hpp"

#include "gui/button_element.hpp"
#include "gui/float_input_element.hpp"
#include "gui/space_element.hpp"
#include "gui/text_element.hpp"
#include "scene/component.hpp"
#include "utils/file_utils.hpp"

#include <format>
#include <fstream>

#include "yaml-cpp/yaml.h"

namespace narechi::editor
{
    inspector_panel::inspector_panel(entity_selection_context* selection_ctx)
        : editor_panel("Inspector")
        , window(gui::window::create({ .name = this->name }))
        , selection_ctx(selection_ctx)
    {
        entity_name_element = gui::text_element::create({});
        component_input_element = gui::text_input_element::create({
            .width = 200.0f,
            .label_on_left = false,
            .bottom_of_window = true,
            .bottom_margin = 90.0f,
        });
        add_component_button = gui::button_element::create({
            .same_line = true,
            .label = "Add Component",
            .on_click =
                [&]()
            {
                current_result
                    = add_component(component_input_element->get_text());
            },
        });
    }

    void inspector_panel::render()
    {
        bool render = static_cast<bool>(selection_ctx) && selection_ctx->active;
        if (render)
        {
            entity_name_element->set_text(
                std::string(selection_ctx->selected_entity.name()));
        }

        window->render(
            [&]()
            {
                if (!render)
                {
                    return;
                }
                entity_name_element->render();

                gui::space_element::create({ .lines = 1 })->render();
                gui::text_element::create({ .text = "Components" })->render();

                if (selection_ctx->selected_entity
                        .has<scene::component::position>())
                {
                    auto& position_value
                        = selection_ctx->selected_entity
                              .get_mut<scene::component::position>()
                              ->value;

                    const std::string custom_id[2] = { "pos1", "pos2" };

                    gui::text_element::create({
                                                  .text = "Position",
                                              })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[0],
                            .label = "X: ",
                            .value = &position_value.x,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[1],
                            .label = "Y: ",
                            .value = &position_value.y,
                            .same_line = true,
                        })
                        ->render();
                }

                if (selection_ctx->selected_entity
                        .has<scene::component::rotation>())
                {
                    auto& value = selection_ctx->selected_entity
                                      .get_mut<scene::component::rotation>()
                                      ->z;

                    gui::text_element::create({
                                                  .text = "Rotation",
                                              })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = "rotation_inspector_value",
                            .label = "Z: ",
                            .value = &value,
                        })
                        ->render();
                }

                if (selection_ctx->selected_entity
                        .has<scene::component::scale>())
                {
                    auto& value = selection_ctx->selected_entity
                                      .get_mut<scene::component::scale>()
                                      ->value;

                    const std::string custom_id[2] = { "scale1", "scale2" };

                    gui::text_element::create({
                                                  .text = "Scale",
                                              })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[0],
                            .label = "X: ",
                            .value = &value.x,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[1],
                            .label = "Y: ",
                            .value = &value.y,
                            .same_line = true,
                        })
                        ->render();
                }

                if (selection_ctx->selected_entity
                        .has<scene::component::scene_camera>())
                {
                    auto& clear_color
                        = selection_ctx->selected_entity
                              .get_mut<scene::component::scene_camera>()
                              ->clear_color;

                    gui::text_element::create({
                                                  .text = "Scene Camera",
                                              })
                        ->render();
                    gui::text_element::create({
                                                  .text = "Clear Color",
                                              })
                        ->render();

                    // Render vector
                    constexpr float width = 60.0f;
                    constexpr float label_gap = -15.0f;

                    const std::string custom_id[4]
                        = { "cc1", "cc2", "cc3", "cc4" };

                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[0],
                            .width = width,
                            .label_gap = label_gap,
                            .label = "R: ",
                            .value = &clear_color.r,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[1],
                            .width = width,
                            .label_gap = label_gap,
                            .label = "G: ",
                            .value = &clear_color.g,
                            .same_line = true,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[2],
                            .width = width,
                            .label_gap = label_gap,
                            .label = "B: ",
                            .value = &clear_color.b,
                            .same_line = true,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .custom_id = custom_id[3],
                            .width = width,
                            .label_gap = label_gap,
                            .label = "A: ",
                            .value = &clear_color.a,
                            .same_line = true,
                        })
                        ->render();
                }

                if (selection_ctx->selected_entity
                        .has<scene::component::sprite>())
                {
                    auto sprite = selection_ctx->selected_entity
                                      .get_mut<scene::component::sprite>();
                    auto& texture_asset_guid = sprite->texture_asset_guid;
                    auto& rotation_offset = sprite->rotation_offset;

                    gui::text_element::create({
                                                  .text = "Sprite",
                                              })
                        ->render();

                    constexpr float width = 60.0f;
                    gui::float_input_element::create(
                        {
                            .custom_id = "sprite_rotation_offset",
                            .width = width,
                            .label = "Rotation Offset: ",
                            .value = &rotation_offset,
                        })
                        ->render();

                    // gui::text_input_element::create(
                    //     {
                    //         .width = 100.0f,
                    //         .label_on_left = true,
                    //         .label = "Sprite",
                    //         .text = &texture_asset_guid,
                    //         .owning = false,
                    //     })
                    //     ->render();
                    auto sprite_asset = app::get()
                                            .get_asset_database()
                                            .get_asset<asset::sprite_asset>(
                                                texture_asset_guid);
                    if (sprite_asset)
                    {
                        gui::image_element::create(
                            {
                                .texture = sprite_asset->get_texture(),
                                .width = 32,
                                .height = 32,
                                .flip_vertically = true,
                            })
                            ->render();
                    }

                    gui::button_element::create(
                        {
                            .same_line = true,
                            .label = "Select",
                            .on_click =
                                [&texture_asset_guid]()
                            {
                                auto sprite_asset_path
                                    = utils::file::open_file_dialog({ .filters
                                        = { { { "narechi sprite asset",
                                            "nrcsprite" } } } });
                                if (sprite_asset_path.has_value())
                                {
                                    std::string data
                                        = utils::file::open_file_as_string(
                                            sprite_asset_path.value());

                                    YAML::Node node = YAML::Load(data);
                                    texture_asset_guid
                                        = node["ID"].as<std::string>();
                                }
                            },
                        })
                        ->render();
                }

                component_input_element->render();
                add_component_button->render();
                auto add_component_message = get_add_component_message();
                if (add_component_message)
                {
                    gui::text_element::create({
                                                  .text = add_component_message,
                                              })
                        ->render();
                }
            });
    }

    inspector_panel::add_component_result inspector_panel::add_component(
        const std::string& component_name)
    {
        if (!selection_ctx || !selection_ctx->active)
        {
            return add_component_result::selection_ctx_null;
        }

        flecs::world world = selection_ctx->selected_entity.world();

        // Attempt to find component
        flecs::entity component_entity = world.lookup(component_name.c_str());
        if (component_entity == 0)
        {
            return add_component_result::component_does_not_exist;
        }

        if (selection_ctx->selected_entity.has(component_entity))
        {
            return add_component_result::component_already_added;
        }
        else
        {
            selection_ctx->selected_entity.add(component_entity);
            return add_component_result::successful;
        }

        NRC_CORE_FATAL("Add component result is none");
        return add_component_result::none;
    }

    const char* inspector_panel::get_add_component_message() const
    {
        switch (current_result)
        {
        case add_component_result::selection_ctx_null:
            NRC_CORE_FATAL("Selection context is null");
            break;
        case add_component_result::component_does_not_exist:
            return "Component does not exist";
            break;
        case add_component_result::component_already_added:
            return "Component already added on entity";
        case add_component_result::successful:
            return "Successful";
        case add_component_result::none:
            return nullptr;
            break;
        }
    }
}
