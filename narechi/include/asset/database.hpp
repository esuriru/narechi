#pragma once

#include "core/core.hpp"
#include "core/assert.hpp"

#include <unordered_map>
#include <string>

namespace narechi::asset
{
    class database
    {
    public:
        database() = default;

        template<typename T>
        std::string add_asset(sptr<T> asset)
        {
            NRC_ASSERT(
                !asset->get_guid().empty(), "Asset GUID cannot be empty");
            asset_map[asset->get_guid()] = asset;
            return asset->get_guid();
        }

        template<typename T>
        sptr<T> get_asset(const std::string& guid)
        {
            const auto& it = asset_map.find(guid);
            return it != asset_map.end() ?
                std::static_pointer_cast<T>(it->second) :
                nullptr;
        }

    private:
        std::unordered_map<std::string, sptr<void>> asset_map;
    };
}