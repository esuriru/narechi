#pragma once

#define NRC_FORWARD_DECL_CLASS(ns, class_name) \
    namespace ns                               \
    {                                          \
        class class_name;                      \
    }

#ifdef NRC_PLATFORM_WINDOWS
    #ifdef NRC_BUILD_DLL
        #define NRC_API __declspec(dllexport)
    #else
        #define NRC_API __declspec(dllimport)
    #endif
#else
    #error "narechi only runs on windows"
#endif

#define NRC_BIND_FN(fn)                                         \
    [this](auto&&... args) -> decltype(auto)                    \
    {                                                           \
        return this->fn(std::forward<decltype(args)>(args)...); \
    }

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