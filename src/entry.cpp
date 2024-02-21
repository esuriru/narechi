#include <iostream>

#include "core/logger.hpp"

int main()
{
    narechi::core_logger.log(
        narechi::logger::log_level::info, "Test ", "Bam");
}
