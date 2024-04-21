#include "vulkan_renderer_api.hpp"

#include "core/assert.hpp"

// NOTE: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
namespace narechi
{
    void vulkan_renderer_api::init()
    {
        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "narechi window";
        app_info.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
        app_info.pEngineName = "narechi engine";
        app_info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info;
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        uint32_t glfw_extension_count = 0;
        const char** glfw_extensions = nullptr;

        glfw_extensions = glfwGetRequiredInstanceExtensions(
            &glfw_extension_count);
        
        create_info.enabledExtensionCount = glfw_extension_count;
        create_info.ppEnabledExtensionNames = glfw_extensions;

        create_info.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&create_info, nullptr, &instance);
        NRC_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan Instance");
    }

    void vulkan_renderer_api::cleanup()
    {

    }
}