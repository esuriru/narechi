#pragma once

#include <core/logger.hpp>

#include <rendering/renderer_api.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

namespace narechi
{
    using std::vector;

    class vulkan_renderer_api final : public renderer_api 
    {
    public:
        vulkan_renderer_api() = default;
        ~vulkan_renderer_api() = default;

        void init() override;
        void cleanup() override;
    
    private:
        const vector<const char*> validation_layers 
        {
            "VK_LAYER_KHRONOS_validation" 
        };


        VkInstance instance;
        VkDebugUtilsMessengerEXT debug_messenger;

        void create_instance();
        vector<const char*> get_required_extensions() const;

        void setup_debug_messenger();
        VkResult create_debug_utils_messenger_ext(VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* create_info,
            const VkAllocationCallbacks* allocator,
            VkDebugUtilsMessengerEXT* debug_messenger);
        void destroy_debug_utils_messenge_ext(VkInstance instance,
            VkDebugUtilsMessengerEXT debug_messenger,
            const VkAllocationCallbacks* allocator);

        void check_extensions();
        bool validation_layer_supported();

#ifdef NRC_DEBUG
        const bool enable_validation_layers = true;
#else 
        const bool enable_validation_layers = false;
#endif
    };
}