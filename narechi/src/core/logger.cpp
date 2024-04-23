#include "core/logger.hpp"

namespace narechi
{
    // logger core_logger = logger("CORE");

    logger::logger(std::string_view name)
        : output_format("[{}] {}:"), name(name)
    {
    }
}