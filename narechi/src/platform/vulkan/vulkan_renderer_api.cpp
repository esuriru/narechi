#include "platform/vulkan/vulkan_renderer_api.hpp"

#include "GLFW/glfw3.h"
#include "core/app.hpp"
#include "core/assert.hpp"
#include "vulkan/vulkan_core.h"

#include <string.h>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>
#include <winnt.h>

// TODO: Possible Verify macro for each create check.

// NOTE: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
namespace narechi
{
    using std::vector;

#ifdef NRC_DEBUG
    constexpr bool enable_validation_layers = true;
#else
    constexpr bool enable_validation_layers = false;
#endif

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
        create_surface();
        pick_physical_device();
        create_logical_device();
        create_swap_chain();
        create_render_pass();
        create_graphics_pipeline();
        create_framebuffers();
        create_command_pool();
        create_command_buffer();
        create_sync_objects();
    }

    void vulkan_renderer_api::cleanup()
    {
        vkDestroySemaphore(device, image_available_semaphore, nullptr);
        vkDestroySemaphore(device, render_finished_semaphore, nullptr);
        vkDestroyFence(device, in_flight_fence, nullptr);

        vkDestroyCommandPool(device, command_pool, nullptr);

        for (auto framebuffer : swap_chain_frame_buffers)
        {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }

        vkDestroyPipeline(device, graphics_pipeline, nullptr);
        vkDestroyPipelineLayout(device, pipeline_layout, nullptr);
        vkDestroyRenderPass(device, render_pass, nullptr);

        for (auto image_view : swap_chain_image_views)
        {
            vkDestroyImageView(device, image_view, nullptr);
        }

        vkDestroySwapchainKHR(device, swap_chain, nullptr);
        vkDestroyDevice(device, nullptr);

        if (enable_validation_layers)
        {
            destroy_debug_utils_messenge_ext(
                instance, debug_messenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
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

    void vulkan_renderer_api::create_surface()
    {
        // TODO - This seems fishy. Probably needs some abstraction
        NRC_VERIFY(glfwCreateWindowSurface(instance,
                       reinterpret_cast<GLFWwindow*>(
                           app::get().get_window().get_native_internal()),
                       nullptr,
                       &surface)
                == VK_SUCCESS,
            "Could not create window surface");
        NRC_CORE_LOG("Vulkan window surface created");
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

        // TODO - Can place the rvalue into the bool condition,
        // but not going to for now
        bool extensions_supported = device_extensions_supported(device);

        if (!extensions_supported)
        {
            return false;
        }

        bool swap_chain_adequate = false;
        auto swap_chain_support_props = get_swap_chain_support_props(device);
        swap_chain_adequate = !swap_chain_support_props.formats.empty()
            && !swap_chain_support_props.present_modes.empty();

        return indices.is_complete() && swap_chain_adequate;
    }

    bool vulkan_renderer_api::device_extensions_supported(
        VkPhysicalDevice device) const
    {
        uint32_t extension_count = 0;
        vkEnumerateDeviceExtensionProperties(
            device, nullptr, &extension_count, nullptr);

        vector<VkExtensionProperties> extensions(extension_count);
        vkEnumerateDeviceExtensionProperties(
            device, nullptr, &extension_count, extensions.data());

        std::set<std::string> required_extensions(
            device_extensions.begin(), device_extensions.end());

        for (const auto& extension : extensions)
        {
            required_extensions.erase(extension.extensionName);
        }

        return required_extensions.empty();
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
            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(
                device, i, surface, &present_support);

            if (present_support)
            {
                indices.present_family = i;
            }

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

        vector<VkDeviceQueueCreateInfo> queue_create_infos {};
        std::set<uint32_t> unique_queue_families {
            indices.graphics_family.value(), indices.present_family.value()
        };

        float queue_priority = 1.0f;

        for (uint32_t queue_family : unique_queue_families)
        {
            VkDeviceQueueCreateInfo queue_create_info {};
            queue_create_info.sType
                = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex
                = indices.graphics_family.value();
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queue_priority;
            queue_create_infos.push_back(queue_create_info);
        }

        VkPhysicalDeviceFeatures device_features {};
        vkGetPhysicalDeviceFeatures(physical_device, &device_features);

        VkDeviceCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount
            = static_cast<uint32_t>(queue_create_infos.size());
        create_info.pQueueCreateInfos = queue_create_infos.data();

        create_info.pEnabledFeatures = &device_features;

        create_info.enabledExtensionCount
            = static_cast<uint32_t>(device_extensions.size());
        create_info.ppEnabledExtensionNames = device_extensions.data();

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
        vkGetDeviceQueue(
            device, indices.present_family.value(), 0, &graphics_queue);
    }

    void vulkan_renderer_api::create_swap_chain()
    {
        auto swap_chain_support = get_swap_chain_support_props(physical_device);

        auto surface_format
            = get_swap_surface_format(swap_chain_support.formats);
        auto present_mode
            = get_swap_present_mode(swap_chain_support.present_modes);
        auto extent = get_swap_extent(swap_chain_support.capabilites);

        uint32_t image_count = swap_chain_support.capabilites.minImageCount + 1;

        // Clamp the image count
        if (swap_chain_support.capabilites.maxImageCount > 0
            && image_count > swap_chain_support.capabilites.maxImageCount)
        {
            image_count = swap_chain_support.capabilites.maxImageCount;
        }

        VkSwapchainCreateInfoKHR create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        create_info.surface = surface;
        create_info.minImageCount = image_count;
        create_info.imageFormat = surface_format.format;
        create_info.imageColorSpace = surface_format.colorSpace;
        create_info.imageExtent = extent;
        create_info.imageArrayLayers = 1;
        create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        auto indices = find_queue_families(physical_device);
        uint32_t queue_family_indices[] { indices.graphics_family.value(),
            indices.present_family.value() };

        if (indices.graphics_family != indices.present_family)
        {
            create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            create_info.queueFamilyIndexCount = 2;
            create_info.pQueueFamilyIndices = queue_family_indices;
        }
        else
        {
            create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            create_info.queueFamilyIndexCount = 0;
            create_info.pQueueFamilyIndices = nullptr;
        }

        create_info.preTransform
            = swap_chain_support.capabilites.currentTransform;
        create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        create_info.presentMode = present_mode;
        create_info.clipped = VK_TRUE;

        create_info.oldSwapchain = VK_NULL_HANDLE;

        NRC_VERIFY(
            vkCreateSwapchainKHR(device, &create_info, nullptr, &swap_chain)
                == VK_SUCCESS,
            "Failed to create Vulkan swap chain");
        NRC_CORE_LOG("Vulkan swap chain created");

        vkGetSwapchainImagesKHR(device, swap_chain, &image_count, nullptr);
        swap_chain_images.resize(image_count);
        vkGetSwapchainImagesKHR(
            device, swap_chain, &image_count, swap_chain_images.data());

        swap_chain_image_format = surface_format.format;
        swap_chain_extent = extent;
    }

    vulkan_renderer_api::swap_chain_support_props
    vulkan_renderer_api::get_swap_chain_support_props(
        VkPhysicalDevice device) const
    {
        swap_chain_support_props props {};
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
            device, surface, &props.capabilites);

        uint32_t format_count;
        vkGetPhysicalDeviceSurfaceFormatsKHR(
            device, surface, &format_count, nullptr);

        if (format_count != 0)
        {
            props.formats.resize(format_count);
            vkGetPhysicalDeviceSurfaceFormatsKHR(
                device, surface, &format_count, props.formats.data());
        }

        uint32_t present_mode_count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            device, surface, &present_mode_count, nullptr);

        if (present_mode_count != 0)
        {
            props.present_modes.resize(present_mode_count);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device,
                surface,
                &present_mode_count,
                props.present_modes.data());
        }

        return props;
    }

    VkSurfaceFormatKHR vulkan_renderer_api::get_swap_surface_format(
        const std::vector<VkSurfaceFormatKHR>& available_formats) const
    {
        for (const auto& available_format : available_formats)
        {
            if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB
                && available_format.colorSpace
                    == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return available_format;
            }
        }

        return available_formats.front();
    }

    VkPresentModeKHR vulkan_renderer_api::get_swap_present_mode(
        const std::vector<VkPresentModeKHR>& available_present_modes) const
    {
        for (const auto& available_present_mode : available_present_modes)
        {
            if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return available_present_mode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D vulkan_renderer_api::get_swap_extent(
        const VkSurfaceCapabilitiesKHR& capabilities) const
    {
        if (capabilities.currentExtent.width
            != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }

        int width, height;
        glfwGetFramebufferSize(
            reinterpret_cast<GLFWwindow*>(
                app::get().get_window().get_native_internal()),
            &width,
            &height);

        VkExtent2D extent { static_cast<uint32_t>(width),
            static_cast<uint32_t>(height) };

        extent.width = std::clamp(extent.width,
            capabilities.minImageExtent.width,
            capabilities.maxImageExtent.width);
        extent.height = std::clamp(extent.height,
            capabilities.minImageExtent.height,
            capabilities.maxImageExtent.height);

        return extent;
    }

    void vulkan_renderer_api::create_image_views()
    {
        size_t swap_chain_images_count = swap_chain_images.size();
        swap_chain_image_views.resize(swap_chain_images_count);

        for (size_t i = 0; i < swap_chain_images_count; ++i)
        {
            VkImageViewCreateInfo create_info {};

            create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            create_info.image = swap_chain_images[i];
            create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            create_info.format = swap_chain_image_format;

            create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

            create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            create_info.subresourceRange.baseMipLevel = 0;
            create_info.subresourceRange.levelCount = 1;
            create_info.subresourceRange.baseArrayLayer = 0;
            create_info.subresourceRange.layerCount = 1;

            NRC_VERIFY(
                vkCreateImageView(
                    device, &create_info, nullptr, &swap_chain_image_views[i])
                    != VK_SUCCESS,
                "Failed to create a Vulkan image view");
        }
    }

    void vulkan_renderer_api::create_graphics_pipeline()
    {
        auto raw_vert_shader = read_file("shaders/vert.spv");
        auto raw_frag_shader = read_file("shaders/frag.spv");

        VkShaderModule vert_shader_module
            = create_shader_module(raw_vert_shader);
        VkShaderModule frag_shader_module
            = create_shader_module(raw_frag_shader);

        VkPipelineShaderStageCreateInfo vert_shader_stage_info {};
        vert_shader_stage_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vert_shader_stage_info.module = vert_shader_module;
        vert_shader_stage_info.pName = "main";

        VkPipelineShaderStageCreateInfo frag_shader_stage_info {};
        frag_shader_stage_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        frag_shader_stage_info.module = frag_shader_module;
        frag_shader_stage_info.pName = "main";

        VkPipelineShaderStageCreateInfo shader_stages[] {
            vert_shader_stage_info, frag_shader_stage_info
        };

        const vector<VkDynamicState> dynamic_states { VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR };

        VkPipelineDynamicStateCreateInfo dynamic_state_info {};
        dynamic_state_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic_state_info.dynamicStateCount
            = static_cast<uint32_t>(dynamic_states.size());
        dynamic_state_info.pDynamicStates = dynamic_states.data();

        VkPipelineVertexInputStateCreateInfo vertex_input_info {};
        vertex_input_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_info.vertexBindingDescriptionCount = 0;
        vertex_input_info.pVertexBindingDescriptions = nullptr;
        vertex_input_info.vertexAttributeDescriptionCount = 0;
        vertex_input_info.pVertexAttributeDescriptions = nullptr;

        VkPipelineInputAssemblyStateCreateInfo input_assembly_info {};
        input_assembly_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        input_assembly_info.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport {};
        viewport.x = viewport.y = 0.0f;
        viewport.width = static_cast<float>(swap_chain_extent.width);
        viewport.height = static_cast<float>(swap_chain_extent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor {};
        scissor.offset = { 0, 0 };
        scissor.extent = swap_chain_extent;

        VkPipelineViewportStateCreateInfo viewport_state_info {};
        viewport_state_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state_info.viewportCount = 1;
        viewport_state_info.pViewports = &viewport;
        viewport_state_info.scissorCount = 1;
        viewport_state_info.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer_info {};
        rasterizer_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer_info.depthClampEnable = VK_FALSE;
        rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
        rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer_info.lineWidth = 1.0f;
        rasterizer_info.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer_info.depthBiasEnable = VK_FALSE;
        rasterizer_info.depthBiasConstantFactor = 0.0f;
        rasterizer_info.depthBiasClamp = 0.0f;
        rasterizer_info.depthBiasSlopeFactor = 0.0f;

        VkPipelineMultisampleStateCreateInfo multisample_info {};
        multisample_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample_info.sampleShadingEnable = VK_FALSE;
        multisample_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisample_info.minSampleShading = 1.0f;
        multisample_info.pSampleMask = nullptr;
        multisample_info.alphaToCoverageEnable = VK_FALSE;
        multisample_info.alphaToOneEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState color_blend_attachment {};
        color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
            | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_G_BIT
            | VK_COLOR_COMPONENT_A_BIT;
        color_blend_attachment.blendEnable = VK_TRUE;
        color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        color_blend_attachment.dstColorBlendFactor
            = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo color_blend_info {};
        color_blend_info.sType
            = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blend_info.logicOpEnable = VK_FALSE;
        color_blend_info.logicOp = VK_LOGIC_OP_COPY;
        color_blend_info.attachmentCount = 1;
        color_blend_info.pAttachments = &color_blend_attachment;
        color_blend_info.blendConstants[0] = 0.0f;
        color_blend_info.blendConstants[1] = 0.0f;
        color_blend_info.blendConstants[2] = 0.0f;
        color_blend_info.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo layout_info {};
        layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layout_info.setLayoutCount = 0;
        layout_info.pSetLayouts = nullptr;
        layout_info.pushConstantRangeCount = 0;
        layout_info.pPushConstantRanges = nullptr;

        VkResult layout_result = vkCreatePipelineLayout(
            device, &layout_info, nullptr, &pipeline_layout);
        NRC_VERIFY(layout_result == VK_SUCCESS,
            "Could not create Vulkan pipeline layout");
        NRC_CORE_LOG("Vulkan pipeline layout created");

        VkGraphicsPipelineCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        create_info.stageCount = 2;
        create_info.pStages = shader_stages;
        create_info.pVertexInputState = &vertex_input_info;
        create_info.pInputAssemblyState = &input_assembly_info;
        create_info.pViewportState = &viewport_state_info;
        create_info.pRasterizationState = &rasterizer_info;
        create_info.pMultisampleState = &multisample_info;
        create_info.pDepthStencilState = nullptr;
        create_info.pColorBlendState = &color_blend_info;
        create_info.pDynamicState = &dynamic_state_info;
        create_info.layout = pipeline_layout;
        create_info.renderPass = render_pass;
        create_info.subpass = 0;
        create_info.basePipelineHandle = VK_NULL_HANDLE;
        create_info.basePipelineIndex = -1;

        VkResult result = vkCreateGraphicsPipelines(device,
            VK_NULL_HANDLE,
            1,
            &create_info,
            nullptr,
            &graphics_pipeline);
        NRC_VERIFY(
            result == VK_SUCCESS, "Could not create Vulkan graphics pipeline");
        NRC_CORE_LOG("Vulkan graphics pipeline created");

        vkDestroyShaderModule(device, frag_shader_module, nullptr);
        vkDestroyShaderModule(device, vert_shader_module, nullptr);
    }

    std::string vulkan_renderer_api::read_file(const std::string& file_path)
    {
        std::ifstream file(file_path, std::ios::ate | std::ios::binary);

        NRC_ASSERT(file && file.is_open(),
            "Failed to open file. File path: ",
            file_path);

        size_t file_size = static_cast<size_t>(file.tellg());
        NRC_ASSERT(file_size != -1,
            "Could not read from opened file. File path: ",
            file_path);

        std::string buffer;
        buffer.resize(file_size);

        file.seekg(0);
        file.read(buffer.data(), file_size);

        return buffer;
    }

    VkShaderModule vulkan_renderer_api::create_shader_module(
        const std::string& raw_shader)
    {
        VkShaderModuleCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = raw_shader.size();
        create_info.pCode
            = reinterpret_cast<const uint32_t*>(raw_shader.data());

        VkShaderModule shader_module;
        VkResult result = vkCreateShaderModule(
            device, &create_info, nullptr, &shader_module);
        NRC_VERIFY(result == VK_SUCCESS, "Failed to create shader module");
        NRC_CORE_LOG("Vulkan Shader Module created");

        return shader_module;
    }

    void vulkan_renderer_api::create_render_pass()
    {
        VkAttachmentDescription color_attachment {};
        color_attachment.format = swap_chain_image_format;
        color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment_reference {};
        color_attachment_reference.attachment = 0;
        color_attachment_reference.layout
            = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &color_attachment_reference;

        VkRenderPassCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        create_info.attachmentCount = 1;
        create_info.pAttachments = &color_attachment;
        create_info.subpassCount = 1;
        create_info.pSubpasses = &subpass;

        VkResult result
            = vkCreateRenderPass(device, &create_info, nullptr, &render_pass);
        NRC_VERIFY(result == VK_SUCCESS, "Could not create Vulkan render pass");
        NRC_CORE_LOG("Vulkan render pass created");
    }

    void vulkan_renderer_api::create_framebuffers()
    {
        swap_chain_frame_buffers.resize(swap_chain_image_views.size());

        for (size_t i = 0; i < swap_chain_image_views.size(); ++i)
        {
            VkImageView attachments[] { swap_chain_image_views[i] };

            VkFramebufferCreateInfo create_info {};
            create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            create_info.renderPass = render_pass;
            create_info.attachmentCount = 1;
            create_info.pAttachments = attachments;
            create_info.width = swap_chain_extent.width;
            create_info.height = swap_chain_extent.height;
            create_info.layers = 1;

            VkResult result = vkCreateFramebuffer(
                device, &create_info, nullptr, &swap_chain_frame_buffers[i]);
            NRC_VERIFY(
                result == VK_SUCCESS, "Could not create Vulkan framebuffer");
            NRC_CORE_LOG("Vulkan framebuffer index ", i, " created");
        }
    }

    void vulkan_renderer_api::create_command_pool()
    {
        auto queue_family_indices = find_queue_families(physical_device);

        VkCommandPoolCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        create_info.queueFamilyIndex
            = queue_family_indices.graphics_family.value();

        VkResult result
            = vkCreateCommandPool(device, &create_info, nullptr, &command_pool);
        NRC_VERIFY(
            result == VK_SUCCESS, "Could not create Vulkan command pool");
        NRC_CORE_LOG("Vulkan command pool created");
    }

    void vulkan_renderer_api::create_command_buffer()
    {
        VkCommandBufferAllocateInfo allocate_info {};
        allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocate_info.commandPool = command_pool;
        allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocate_info.commandBufferCount = 1;

        VkResult result
            = vkAllocateCommandBuffers(device, &allocate_info, &command_buffer);
        NRC_VERIFY(
            result == VK_SUCCESS, "Could not allocate Vulkan command buffer");
        NRC_CORE_LOG("Allocated vulkan comand buffers");
    }

    void vulkan_renderer_api::record_command_buffer(
        VkCommandBuffer command_buffer, uint32_t image_index)
    {
        VkCommandBufferBeginInfo begin_info {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = 0;
        begin_info.pInheritanceInfo = nullptr;

        VkResult begin_result
            = vkBeginCommandBuffer(command_buffer, &begin_info);
        NRC_VERIFY(begin_result == VK_SUCCESS,
            "Could not begin recording Vulkan command buffer");
        NRC_CORE_LOG("Begin recording vulkan command buffer");

        VkRenderPassBeginInfo render_pass_info {};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = render_pass;
        render_pass_info.framebuffer = swap_chain_frame_buffers[image_index];
        render_pass_info.renderArea.offset = { 0, 0 };
        render_pass_info.renderArea.extent = swap_chain_extent;

        VkClearValue clear_color = { { { 0.527f, 0.807f, 0.980f, 1.0f } } };
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clear_color;

        vkCmdBeginRenderPass(
            command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(
            command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphics_pipeline);

        VkViewport viewport {};
        viewport.x = viewport.y = 0.0f;
        viewport.width = static_cast<float>(swap_chain_extent.width);
        viewport.height = static_cast<float>(swap_chain_extent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor {};
        scissor.offset = { 0, 0 };
        scissor.extent = swap_chain_extent;

        vkCmdDraw(command_buffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(command_buffer);

        VkResult end_result = vkEndCommandBuffer(command_buffer);
        NRC_VERIFY(end_result == VK_SUCCESS,
            "Could not end recording Vulkan command buffer");
        NRC_CORE_LOG("End recording vulkan command buffer");
    }

    void vulkan_renderer_api::create_sync_objects()
    {
        VkSemaphoreCreateInfo semaphore_info {};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fence_info {};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

        NRC_VERIFY(
            vkCreateSemaphore(
                device, &semaphore_info, nullptr, &image_available_semaphore)
                    == VK_SUCCESS
                && vkCreateSemaphore(device,
                       &semaphore_info,
                       nullptr,
                       &render_finished_semaphore)
                    == VK_SUCCESS
                && vkCreateFence(device, &fence_info, nullptr, &in_flight_fence)
                    == VK_SUCCESS,
            "Failed to create Vulkan synchronization objects");
        NRC_CORE_LOG("Vulkan sync objects created");
    }
}
