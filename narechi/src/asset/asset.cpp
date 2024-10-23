#include "asset/asset.hpp"

#include "core/assert.hpp"

#include <fstream>

namespace narechi::asset
{
    asset::asset(const std::filesystem::path& path)
        : path(path)
    {
    }

    const std::filesystem::path& asset::get_path()
    {
        return path;
    }

    void asset::load()
    {
        std::ifstream file_in(path);
        std::ostringstream buffer;
        buffer << file_in.rdbuf();

        data = buffer.str();

        deserialize();
    }

    void asset::write()
    {
        serialize();

        std::ofstream file_out(path);
        NRC_ASSERT(file_out.is_open(), "Asset directory is not valid");
        file_out << data;
    }
}
