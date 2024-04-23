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
        struct queue_family_indices
        {
            uint32_t graphics_family;
        };

#ifdef NRC_DEBUG
        const bool enable_validation_layers = true;
#else
        const bool enable_validation_layers = false;
#endif

        const vector<const char*> validation_layers {
            "VK_LAYER_KHRONOS_validation"
        };

        VkInstance instance;
        VkDebugUtilsMessengerEXT debug_messenger;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;

        void create_instance();
        void check_extensions();
        vector<const char*> get_required_extensions() const;
        bool validation_layer_supported();

        void setup_debug_messenger();
        VkDebugUtilsMessengerCreateInfoEXT get_debug_messenger_create_info()
            const;
        VkResult create_debug_utils_messenger_ext(VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* create_info,
            const VkAllocationCallbacks* allocator,
            VkDebugUtilsMessengerEXT* debug_messenger);
        void destroy_debug_utils_messenge_ext(VkInstance instance,
            VkDebugUtilsMessengerEXT debug_messenger,
            const VkAllocationCallbacks* allocator);

        void pick_physical_device();
        bool physical_device_suitable(VkPhysicalDevice device) const;
        queue_family_indices find_queue_families(VkPhysicalDevice device);
    };
}