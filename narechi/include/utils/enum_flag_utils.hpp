#pragma once

#include <type_traits>

namespace narechi
{
    template<typename E>
    constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
    {
        return static_cast<typename std::underlying_type<E>::type>(e);
    }

#define NRC_MEMBER_ENUM_FLAG_OPERATORS(enum_name)                       \
    friend constexpr enum enum_name operator|(                          \
        enum enum_name a, enum enum_name b)                             \
    {                                                                   \
        return static_cast<enum_name>(to_integral(a) | to_integral(b)); \
    }                                                                   \
                                                                        \
    friend constexpr bool operator&(enum enum_name a, enum enum_name b) \
    {                                                                   \
        return static_cast<bool>(to_integral(a) & to_integral(b));      \
    }

#define NRC_ENUM_FLAG_OPERATORS(enum_name)                                 \
    constexpr enum enum_name operator|(enum enum_name a, enum enum_name b) \
    {                                                                      \
        return static_cast<enum_name>(to_integral(a) | to_integral(b));    \
    }                                                                      \
                                                                           \
    constexpr bool operator&(enum enum_name a, enum enum_name b)           \
    {                                                                      \
        return static_cast<bool>(to_integral(a) & to_integral(b));         \
    }
}