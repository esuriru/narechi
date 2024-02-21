#pragma once

#include <iostream>
#include <format>

#include "utils/time_utils.hpp"

namespace narechi
{
    class logger 
    {
    public:
        enum class log_level
        {
            none = 0,
            warn,
            error,
            info,
            debug
        };

        explicit logger();

        template <typename Arg, typename... Args>
        void log(const log_level level, Arg&& arg, Args&&... args)
        {
            // TODO - Singular format string
            std::cout << std::vformat(output_format, 
                std::make_format_args(
                    utils::get_formatted_time())) << " "; 
            std::cout << std::forward<Arg>(arg);
            ((std::cout << std::forward<Args>(args)), ...);
        }
    
    private:
        std::string output_format; 

    };

    static logger core_logger;
}
