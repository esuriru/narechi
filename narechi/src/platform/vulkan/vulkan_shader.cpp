#include "platform/vulkan/vulkan_shader.hpp"

#include "core/assert.hpp"
#include "vulkan/vulkan_core.h"

#include <fstream>

namespace narechi
{
    vulkan_shader::vulkan_shader(std::string name,
        const std::string& vertex_file_path,
        const std::string& fragment_file_path)
        : name(std::move(name))
    {
    }

    void vulkan_shader::bind()
    {
    }

    void vulkan_shader::unbind()
    {
    }

    void vulkan_shader::set_int(const std::string& name, int value)
    {
    }

    const std::string& vulkan_shader::get_name()
    {
        return name;
    }

    std::string vulkan_shader::read_file(const std::string& file_path)
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

    VkShaderModule vulkan_shader::create_shader_module(
        const std::string& raw_shader)
    {
        VkShaderModuleCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = raw_shader.size();
        create_info.pCode
            = reinterpret_cast<const uint32_t*>(raw_shader.data());

        // VkResult result = vkCreateShaderModule(
        // NRC_VERIFY()
    }
}