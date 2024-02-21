#include "time_utils.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <format>

std::string narechi::utils::get_formatted_time()
{
    const auto now = std::chrono::system_clock::now();
    return std::format(R"({:%H:%M:%OS})", now);
}
   