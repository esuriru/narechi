#include <iostream>

#include "core/logger.hpp"

int main()
{
    narechi::logger logger;
    logger.log(narechi::logger::log_level::info, "Test ", "Bam");
}
