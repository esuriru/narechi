#include "vulkan_renderer_api.hpp"

#include "core/assert.hpp"

#include <vector>

// NOTE: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
namespace narechi
{
    void vulkan_renderer_api::init()
    {
        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "narechi window";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "narechi engine";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info{};
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

        NRC_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance");
        NRC_CORE_LOG("Vulkan instance created");

        uint32_t extension_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, 
            nullptr);

        std::vector<VkExtensionProperties> extensions(extension_count);
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, 
            extensions.data());

        NRC_CORE_LOG("Available Vulkan Extensions:");
        for (auto& extension : extensions)
        {
            NRC_CORE_LOG("\t", extension.extensionName);
        }
    }

    void vulkan_renderer_api::cleanup()
    {
        vkDestroyInstance(instance, nullptr);
        NRC_CORE_LOG("Vulkan cleanup done");
    }
}