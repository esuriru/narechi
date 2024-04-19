#pragma once

namespace narechi
{
    class renderer_api
    {
    public:
        enum class api
        {
            none = 0,
            vulkan
        };

        virtual ~renderer_api() = default;

        virtual void init() = 0;
        virtual void cleanup() = 0;

    };
}