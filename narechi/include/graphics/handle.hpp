#pragma once

#include "core/core.hpp"

#include <cstdint>

namespace narechi::graphics
{
    class NRC_API handle
    {
    public:
        virtual ~handle() = default;

        uint32_t get_id() const;

    protected:
        uint32_t id;
    };
}