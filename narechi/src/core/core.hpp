#pragma once

#ifdef NRC_DEBUG

#endif

#ifdef NRC_PLATFORM_WINDOWS
#else
    #error "narechi only runs on windows"
#endif

#include <memory>

namespace narechi
{
    template<typename T>
    using sptr = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr sptr<T> create_shared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}