#pragma once

#include <cstdint>

namespace narechi::graphics
{
    class handle
    {
    public:
        virtual ~handle() = default;

        uint32_t get_id() const;

    protected:
        uint32_t id;
    };
}