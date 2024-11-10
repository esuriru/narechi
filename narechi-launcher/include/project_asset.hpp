#pragma once

#include <core/core.hpp>

#include "project.hpp"

#include "narechi.hpp"

#include <filesystem>

namespace narechi::editor
{
    class project_asset : public asset::asset
    {
    public:
        project_asset(
            const std::filesystem::path& path, project::project_data* data);
        ~project_asset();

    private:
        project::project_data* project_data;

        void serialize() override;
        void deserialize() override;
    };
}