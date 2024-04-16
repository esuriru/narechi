#pragma once

#include <utils/time_utils.hpp>
#include <core/core.hpp>

#include <iostream>
#include <format>

namespace narechi
{
    class NRC_API logger 
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

        explicit logger(std::string_view name);

        template<typename Arg, typename... Args>
        void log(const log_level level, Arg&& arg, Args&&... args)
        {
            // TODO - Singular format string
            std::cout << std::vformat(output_format, 
                std::make_format_args(
                    utils::get_formatted_time(), name)) << " "; 
            std::cout << std::forward<Arg>(arg);
            ((std::cout << std::forward<Args>(args)), ...);
            std::cout << "\n";
        }
    
    private:
        std::string name;
        std::string output_format; 

    };

    static logger core_logger = logger("CORE");
}

#define NRC_CORE_INFO(...) narechi::core_logger.log(\
    narechi::logger::log_level::info, __VA_ARGS__)
#define NRC_CORE_DEBUG(...) narechi::core_logger.log(\
    narechi::logger::log_level::debug, __VA_ARGS__)
#define NRC_CORE_WARN(...) narechi::core_logger.log(\
    narechi::logger::log_level::warn, __VA_ARGS__)
#define NRC_CORE_LOG(...) narechi::core_logger.log(\
    narechi::logger::log_level::none, __VA_ARGS__)
#define NRC_CORE_ERROR(...) narechi::core_logger.log(\
    narechi::logger::log_level::error, __VA_ARGS__)
