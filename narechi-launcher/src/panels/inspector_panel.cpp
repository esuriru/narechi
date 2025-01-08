#include "panels/inspector_panel.hpp"

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
                // selection_ctx->selected_entity.each(
                //     [this](flecs::id component_id)
                //     {
                //         if (component_id.is_entity())
                //         {
                //             flecs::entity e = component_id.entity();
                //             gui::text_element::create(
                //                 {
                //                     .text = std::string(e.name()),
                //                 })
                //                 ->render();

                //             if (e.name() == "position")
                //             {
                //                 gui::text_element::create({})
                //                     ->render();
                //             }
                //         }
                //     });

                if (selection_ctx->selected_entity
                        .has<scene::component::position>())
                {
                    auto& position_value
                        = selection_ctx->selected_entity
                              .get_mut<scene::component::position>()
                              ->value;

                    gui::text_element::create({
                                                  .text = "Position",
                                              })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .label = "X: ",
                            .value = &position_value.x,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .label = "Y: ",
                            .value = &position_value.y,
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

                    gui::float_input_element::create(
                        {
                            .width = width,
                            .label_gap = label_gap,
                            .label = "R: ",
                            .value = &clear_color.r,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .width = width,
                            .label_gap = label_gap,
                            .label = "G: ",
                            .value = &clear_color.g,
                            .same_line = true,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
                            .width = width,
                            .label_gap = label_gap,
                            .label = "B: ",
                            .value = &clear_color.b,
                            .same_line = true,
                        })
                        ->render();
                    gui::float_input_element::create(
                        {
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
                    auto& texture_asset_guid
                        = selection_ctx->selected_entity
                              .get_mut<scene::component::sprite>()
                              ->texture_asset_guid;

                    gui::text_element::create({
                                                  .text = "Sprite",
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
                                    std::ifstream file_in(
                                        sprite_asset_path.value());
                                    std::ostringstream buffer;
                                    buffer << file_in.rdbuf();

                                    YAML::Node node = YAML::Load(buffer.str());
                                    texture_asset_guid
                                        = node["ID"].as<std::string>();
                                }
                            },
                        })
                        ->render();
                }
            });
    }
}
