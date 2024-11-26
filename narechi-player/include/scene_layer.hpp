#pragma once

#include "narechi.hpp"

namespace narechi::player
{
    class scene_layer : public layer
    {
    public:
        scene_layer();

        void on_attach() override;
        void on_update(float delta_time) override;
        void on_event(event& event) override;

    private:
        sptr<scene::scene> current_scene;

        void invalidate_proj_matrix(float width, float height);
    };
}