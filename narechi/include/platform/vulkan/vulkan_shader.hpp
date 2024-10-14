#pragma once

#include "rendering/shader.hpp"

#include <vulkan/vulkan.h>

namespace narechi
{
    class vulkan_shader : public shader
    {
    public:
        vulkan_shader(std::string name, const std::string& vertex_file_path,
            const std::string& fragment_file_path);

        void bind() override;
        void unbind() override;

        void set_int(const std::string& name, int value) override;

        const std::string& get_name() override;

    private:
        std::string name;

        std::string read_file(const std::string& file_path);
        VkShaderModule create_shader_module(const std::string& raw_shader);
    };
}