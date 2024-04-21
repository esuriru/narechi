#pragma once

#include <rendering/renderer_api.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace narechi
{
    class vulkan_renderer_api final : public renderer_api 
    {
    public:
        vulkan_renderer_api() = default;
        ~vulkan_renderer_api() = default;

        void init() override;
        void cleanup() override;
    
    private:
        VkInstance instance;
    };
}