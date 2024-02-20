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

        template <typename Arg, typename... Args>
        void log(log_level level, Arg&& arg, Args&&... args)
        {
            std::cout << utils::get_formatted_time();
            std::cout << std::forward<Arg>(arg);
            ((std::cout << std::forward<Args>(args)), ...);
        }
    };
}