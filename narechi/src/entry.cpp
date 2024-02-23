#include <iostream>

#include "core/core.hpp"
#include "core/logger.hpp"
#include "core/assert.hpp"

int main()
{
    narechi::core_logger.log(
        narechi::logger::log_level::info, "Test ", "Bam");
    NRC_ASSERT(false, "Test assertion");
}
