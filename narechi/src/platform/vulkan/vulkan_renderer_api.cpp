#include "platform/vulkan/vulkan_renderer_api.hpp"

#include "core/assert.hpp"
#include "vulkan/vulkan_core.h"

#include <string.h>

// NOTE: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
namespace narechi
{
    using std::vector;

    static uptr<logger> validation_layer_logger
        = make_uptr<logger>("Vulkan Validation Layer");

    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
        VkDebugUtilsMessageTypeFlagsEXT message_type,
        const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
        void* user_data)
    {
        // TODO - Convert message severity to log_level
        validation_layer_logger->log(
            logger::log_level::error, callback_data->pMessage);
        return VK_FALSE;
    }

    void vulkan_renderer_api::init()
    {
        create_instance();
        setup_debug_messenger();
        pick_physical_device();
        create_logical_device();
    }

    void vulkan_renderer_api::cleanup()
    {
        vkDestroyDevice(device, nullptr);

        if (enable_validation_layers)
        {
            destroy_debug_utils_messenge_ext(
                instance, debug_messenger, nullptr);
        }

        vkDestroyInstance(instance, nullptr);
        NRC_CORE_INFO("Vulkan cleanup done");
    }

    void vulkan_renderer_api::create_instance()
    {
        NRC_ASSERT(!enable_validation_layers || validation_layer_supported(),
            "Vulkan validation layers requested, but not available");

        VkApplicationInfo app_info {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "narechi window";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "narechi engine";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        check_extensions();
        auto extensions = get_required_extensions();
        create_info.enabledExtensionCount
            = static_cast<uint32_t>(extensions.size());
        create_info.ppEnabledExtensionNames = extensions.data();

        if (enable_validation_layers)
        {
            create_info.enabledLayerCount
                = static_cast<uint32_t>(validation_layers.size());
            create_info.ppEnabledLayerNames = validation_layers.data();

            auto debug_messenger_create_info
                = get_debug_messenger_create_info();
            create_info.pNext
                = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(
                    &debug_messenger_create_info);
        }
        else
        {
            create_info.enabledLayerCount = 0;

            create_info.pNext = nullptr;
        }

        VkResult result = vkCreateInstance(&create_info, nullptr, &instance);

        NRC_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance");
        NRC_CORE_LOG("Vulkan instance created");
    }

    void vulkan_renderer_api::check_extensions()
    {
        uint32_t extension_count = 0;
        vkEnumerateInstanceExtensionProperties(
            nullptr, &extension_count, nullptr);

        vector<VkExtensionProperties> extensions(extension_count);
        vkEnumerateInstanceExtensionProperties(
            nullptr, &extension_count, extensions.data());

        NRC_CORE_LOG("Available Vulkan Extensions:");
        for (auto& extension : extensions)
        {
            NRC_CORE_LOG("\t", extension.extensionName);
        }
    }

    vector<const char*> vulkan_renderer_api::get_required_extensions() const
    {
        uint32_t glfw_extension_count = 0;
        const char** glfw_extensions = nullptr;

        glfw_extensions
            = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

        vector<const char*> extensions(
            glfw_extensions, glfw_extensions + glfw_extension_count);

        if (enable_validation_layers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool vulkan_renderer_api::validation_layer_supported()
    {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(
            &layer_count, available_layers.data());

        for (const char* layer_name : validation_layers)
        {
            bool layer_found = false;

            for (const auto& layer_properties : available_layers)
            {
                if (strcmp(layer_name, layer_properties.layerName) == 0)
                {
                    layer_found = true;
                    break;
                }
            }

            if (!layer_found)
            {
                return false;
            }
        }

        return true;
    }

    void vulkan_renderer_api::setup_debug_messenger()
    {
        if (!enable_validation_layers)
        {
            return;
        }

        auto create_info = get_debug_messenger_create_info();
        VkResult result = create_debug_utils_messenger_ext(
            instance, &create_info, nullptr, &debug_messenger);
        NRC_ASSERT(result == VK_SUCCESS, "Failed to setup debug messenger");
        NRC_CORE_LOG("Vulkan debug messenger created");
    }

    VkDebugUtilsMessengerCreateInfoEXT
    vulkan_renderer_api::get_debug_messenger_create_info() const
    {
        VkDebugUtilsMessengerCreateInfoEXT create_info {};
        create_info.sType
            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity
            = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = debug_callback;
        return create_info;
    }

    VkResult vulkan_renderer_api::create_debug_utils_messenger_ext(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* create_info,
        const VkAllocationCallbacks* allocator,
        VkDebugUtilsMessengerEXT* debug_messenger)
    {
        auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        return func != nullptr ?
            func(instance, create_info, allocator, debug_messenger) :
            VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void vulkan_renderer_api::destroy_debug_utils_messenge_ext(
        VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger,
        const VkAllocationCallbacks* allocator)
    {
        auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func != nullptr)
        {
            func(instance, debug_messenger, allocator);
            NRC_CORE_LOG("Destroyed Vulkan debug messenger");
        }
        else
        {
            NRC_CORE_ERROR("Could not destroy Vulkan debug messenger");
        }
    }

    // TODO - Move this out to a static utils class
    static const char* physical_device_type_to_string(
        VkPhysicalDeviceType device_type)
    {
        switch (device_type)
        {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return "Other Device";
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return "Integrated GPU";
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return "Discrete GPU";
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return "Virtual GPU";
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return "CPU";
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
            break;
        }

        return nullptr;
    }

    void vulkan_renderer_api::pick_physical_device()
    {
        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

        NRC_VERIFY(device_count > 0, "Failed to find Vulkan-compatible GPUs");

        vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

        for (const auto& device : devices)
        {
            if (physical_device_suitable(device))
            {
                physical_device = device;
                break;
            }
        }

        NRC_VERIFY(
            physical_device != VK_NULL_HANDLE, "Failed to find suitable GPU");

        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physical_device, &properties);

        NRC_CORE_LOG("Vulkan is using physical device:");
        NRC_CORE_LOG("\tDevice name: ", properties.deviceName);
        NRC_CORE_LOG("\tDevice type: ",
            physical_device_type_to_string(properties.deviceType));
        NRC_CORE_LOG("\tDriver version: ", properties.driverVersion);
    }

    bool vulkan_renderer_api::physical_device_suitable(
        VkPhysicalDevice device) const
    {
        auto indices = find_queue_families(device);

        return indices.is_complete();
    }

    vulkan_renderer_api::queue_family_indices
    vulkan_renderer_api::find_queue_families(VkPhysicalDevice device) const
    {
        queue_family_indices indices {};

        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(
            device, &queue_family_count, nullptr);

        vector<VkQueueFamilyProperties> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(
            device, &queue_family_count, queue_families.data());

        for (int i = 0; i < queue_family_count; ++i)
        {
            if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphics_family = i;
            }

            if (indices.is_complete())
            {
                break;
            }
        }

        return indices;
    }

    void vulkan_renderer_api::create_logical_device()
    {
        // TODO - Maybe cache the indices when finding a physical device
        queue_family_indices indices = find_queue_families(physical_device);

        VkDeviceQueueCreateInfo queue_create_info {};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = indices.graphics_family.value();
        queue_create_info.queueCount = 1;

        float queue_priority = 1.0f;
        queue_create_info.pQueuePriorities = &queue_priority;

        VkPhysicalDeviceFeatures device_features {};
        vkGetPhysicalDeviceFeatures(physical_device, &device_features);

        VkDeviceCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.pQueueCreateInfos = &queue_create_info;
        create_info.queueCreateInfoCount = 1;

        create_info.pEnabledFeatures = &device_features;

        create_info.enabledExtensionCount = 0;

        if (enable_validation_layers)
        {
            create_info.enabledLayerCount
                = static_cast<uint32_t>(validation_layers.size());
            create_info.ppEnabledLayerNames = validation_layers.data();
        }
        else
        {
            create_info.enabledLayerCount = 0;
        }

        NRC_VERIFY(
            vkCreateDevice(physical_device, &create_info, nullptr, &device)
                == VK_SUCCESS,
            "Failed to create Vulkan logical device");
        NRC_CORE_LOG("Vulkan logical device created");

        vkGetDeviceQueue(
            device, indices.graphics_family.value(), 0, &graphics_queue);
    }
}
