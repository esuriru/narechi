#pragma once

#include <core/core.hpp>

#include "narechi.hpp"

#include <filesystem>

namespace narechi::editor
{
    struct project_properties;

    class project_asset : public asset::asset
    {
    public:
        project_asset(std::filesystem::path&& path, 
            project_properties& props);

        void serialize();
    
    private:
        std::string data;
        project_properties& props;
    };
}