#pragma once

#include <string>

namespace narechi
{
    class layer 
    {
    public:
        layer(const std::string& name) : debug_name(name) {}
        layer(std::string&& name) : debug_name(std::move(name)) {}

        virtual void on_attach() {}
        virtual void on_detach() {}

        virtual void on_update(float ts) {}

    protected:
        std::string debug_name;
    };
}