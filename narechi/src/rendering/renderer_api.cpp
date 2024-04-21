#include "renderer_api.hpp"

#include <platform/vulkan/vulkan_renderer_api.hpp>

namespace narechi
{
    renderer_api::api renderer_api::api_type = 
        renderer_api::api::vulkan;

    uptr<renderer_api> renderer_api::create()
    {
        switch (api_type)
        {
            case renderer_api::api::none:
                // TODO - Fatal here
                break;
            case renderer_api::api::vulkan:
                return make_uptr<vulkan_renderer_api>();
        }

        return nullptr;
    }
}