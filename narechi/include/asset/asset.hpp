#pragma once

#include "core/core.hpp"

#include <filesystem>

namespace narechi::asset
{
    class NRC_API asset
    {
    public:
        asset(const std::filesystem::path& path);

        const std::filesystem::path& get_path() const;

        void load(bool deserialize_only = false);
        void write();

    protected:
        std::string data;
        std::filesystem::path path;
        bool is_owning;

    private:
        virtual void serialize() = 0;
        virtual void deserialize() = 0;
    };
}