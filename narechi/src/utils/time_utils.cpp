#include "time_utils.hpp"

#include <GLFW/glfw3.h>

#include <chrono>
#include <sstream>
#include <iomanip>
#include <format>

namespace narechi
{
    std::string utils::get_formatted_time()
    {
        using namespace std::chrono;

        const auto now
            = floor<seconds>(current_zone()->to_local(system_clock::now()));
        return std::format(R"({:%X})", now);
    }

    float utils::get_time()
    {
#ifdef NRC_PLATFORM_WINDOWS
        return glfwGetTime();
#else
        return 0.0f;
#endif
    }
}
