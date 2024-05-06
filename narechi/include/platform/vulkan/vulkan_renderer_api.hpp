#pragma once

#include "vulkan/vulkan_core.h"
#include <core/logger.hpp>

#include <rendering/renderer_api.hpp>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <vector>
#include <optional>

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
            std::optional<uint32_t> graphics_family;
            std::optional<uint32_t> present_family;

            bool is_complete() const
            {
                return graphics_family.has_value()
                    && present_family.has_value();
            }
        };

        struct swap_chain_support_props
        {
            VkSurfaceCapabilitiesKHR capabilites;
            vector<VkSurfaceFormatKHR> formats;
            vector<VkPresentModeKHR> present_modes;
        };

        const vector<const char*> device_extensions {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        const vector<const char*> validation_layers {
            "VK_LAYER_KHRONOS_validation"
        };

        VkInstance instance;
        VkDebugUtilsMessengerEXT debug_messenger;
        VkSurfaceKHR surface;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphics_queue, present_queue;

        VkSwapchainKHR swap_chain;
        vector<VkImage> swap_chain_images;
        VkFormat swap_chain_image_format;
        VkExtent2D swap_chain_extent;
        vector<VkImageView> swap_chain_image_views;

        VkRenderPass render_pass;
        VkPipelineLayout pipeline_layout;

        VkPipeline graphics_pipeline;

        vector<VkFramebuffer> swap_chain_frame_buffers;

        VkCommandPool command_pool;

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

        void create_surface();

        void pick_physical_device();
        bool physical_device_suitable(VkPhysicalDevice device) const;
        bool device_extensions_supported(VkPhysicalDevice device) const;
        queue_family_indices find_queue_families(VkPhysicalDevice device) const;

        void create_logical_device();

        void create_swap_chain();
        swap_chain_support_props get_swap_chain_support_props(
            VkPhysicalDevice device) const;
        VkSurfaceFormatKHR get_swap_surface_format(
            const std::vector<VkSurfaceFormatKHR>& available_formats) const;
        VkPresentModeKHR get_swap_present_mode(
            const std::vector<VkPresentModeKHR>& available_present_modes) const;
        VkExtent2D get_swap_extent(
            const VkSurfaceCapabilitiesKHR& capabilities) const;

        void create_image_views();

        void create_graphics_pipeline();
        std::string read_file(const std::string& file_path);
        VkShaderModule create_shader_module(const std::string& raw_shader);

        void create_render_pass();

        void create_framebuffers();

        void create_command_pool();
    };
}