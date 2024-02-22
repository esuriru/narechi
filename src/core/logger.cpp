#include "logger.hpp"

narechi::logger::logger(std::string_view name)
    : output_format("[{}] {}:")
    , name(name)
{
}