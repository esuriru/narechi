#include "core/logger.hpp"

#ifdef NRC_PLATFORM_WINDOWS
    #include <windows.h>
#endif

namespace narechi
{
    logger::logger(std::string_view name)
        : output_format("[{}] {}:"), name(name)
    {
        // Reset the text color to the 'original' color
        set_text_color(log_level::none);
    }

    logger::~logger()
    {
        set_text_color(log_level::none);
    }

    void logger::set_text_color(log_level level)
    {
#ifdef NRC_PLATFORM_WINDOWS
        static HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (level)
        {
        case logger::log_level::debug:
        case logger::log_level::info:
            // Green
            SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN);
            break;
        case logger::log_level::none:
            // White
            SetConsoleTextAttribute(console_handle, 15);
            break;
        case logger::log_level::warn:
            // Yellow
            SetConsoleTextAttribute(console_handle, 14);
            break;
        case logger::log_level::error:
            // Red
            SetConsoleTextAttribute(console_handle, FOREGROUND_RED);
            break;
        }
#else
        NRC_CORE_ERROR("Could not set text color for this platform");
#endif
    }
}