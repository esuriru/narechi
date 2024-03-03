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
    sptr<T> make_sptr(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using uptr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    uptr<T> make_uptr(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}