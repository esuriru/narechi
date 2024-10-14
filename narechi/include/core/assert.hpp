#pragma once

#include "core/logger.hpp"

#ifdef NRC_PLATFORM_WINDOWS
    #if defined(__clang__)
        #define NRC_DEBUG_BREAK __builtin_trap()
    #elif defined(__GNUC__) || defined(__GNUG__)
        #define NRC_DEBUG_BREAK __builtin_trap()
    #elif defined(_MSC_VER)
        #define NRC_DEBUG_BREAK __debugbreak()
    #endif
#else
    #define NRC_DEBUG_BREAK
#endif

#ifdef NRC_DEBUG
    #define NRC_ENABLE_ASSERTS
#endif

#define NRC_ENABLE_VERIFY

#ifdef NRC_ENABLE_ASSERTS
    #define NRC_ASSERT(cond, ...)                \
        if (!(cond))                             \
        {                                        \
            NRC_CORE_ERROR("Assertion failed: ", \
                __VA_ARGS__,                     \
                "\n\tat line number: ",          \
                __LINE__,                        \
                "\n\tin file: ",                 \
                __FILE__);                       \
            NRC_DEBUG_BREAK;                     \
        }
#else
    #define NRC_ASSERT(cond, ...)
#endif

#ifdef NRC_ENABLE_VERIFY
    #define NRC_VERIFY(cond, ...)             \
        if (!(cond))                          \
        {                                     \
            NRC_CORE_ERROR("Verify failed: ", \
                __VA_ARGS__,                  \
                "\n\tat line number: ",       \
                __LINE__,                     \
                "\n\tin file: ",              \
                __FILE__);                    \
            NRC_DEBUG_BREAK;                  \
        }
#else
    #define NRC_VERIFY(cond, ...)
#endif