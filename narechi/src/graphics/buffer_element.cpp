#include "graphics/buffer_element.hpp"

namespace narechi::graphics
{
    buffer_element::buffer_element(
        shader_data_type type, const std::string& name, const bool normalized)
        : name(name)
        , type(type)
        , size(shader_data_type_size(type))
        , offset(0)
        , normalized(normalized)
    {
    }


}