#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"

#include "glm/glm.hpp"

#include <string>

namespace narechi::graphics
{
    class shader : public handle
    {
    public:
        shader(const std::string& name);
        virtual ~shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void set_int(const std::string& name, int value) = 0;
        virtual void set_mat4(const std::string& name, const glm::mat4& value)
            = 0;

        virtual const std::string& get_name();

        static sptr<shader> create(const std::string& name,
            const char* vertex_src, const char* fragment_src);

    protected:
        std::string name;
    };
}