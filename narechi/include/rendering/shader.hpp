#pragma once

#include <string>

namespace narechi
{
    class shader
    {
    public:
        virtual ~shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void set_int(const std::string& name, int value) = 0;

        virtual const std::string& get_name() = 0;
    };
}