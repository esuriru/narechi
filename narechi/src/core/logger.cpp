#include "logger.hpp"

namespace narechi
{
    logger::logger(std::string_view name)
        : output_format("[{}] {}:")
        , name(name)
    {
    }
}