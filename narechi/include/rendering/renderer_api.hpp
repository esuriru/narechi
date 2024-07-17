#pragma once

#include "core/core.hpp"

namespace narechi
{
    class renderer_api
    {
    public:
        enum class api
        {
            none = 0,
            opengl,
            vulkan
        };

        virtual ~renderer_api() = default;

        virtual void init() = 0;
        virtual void cleanup() = 0;

        static uptr<renderer_api> create();

        inline static api get_api()
        {
            return api_type;
        }

    private:
        static api api_type;
    };
}