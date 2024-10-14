#pragma once

#include <string>
#include <filesystem>

namespace narechi::editor
{
    struct project_properties
    {
        std::string name;
    };

    class project
    {
    public:
        static void serialize(
            const std::filesystem::path& output_path, const project& project);
        
        project(const project_properties& props);

    private:
        std::string name;
    };
}