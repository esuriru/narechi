#include "time_utils.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <format>

namespace narechi
{
    std::string utils::get_formatted_time()
    {
        using namespace std::chrono;

        const auto now = 
            floor<seconds>(current_zone()->to_local(system_clock::now()));
        return std::format(R"({:%X})", now);
    }
}
   