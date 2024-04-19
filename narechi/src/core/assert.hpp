#pragma once

#include <core/logger.hpp>

#ifdef NRC_DEBUG
    #define NRC_ASSERT(cond, ...)\
    if (!(cond))\
    {\
        NRC_CORE_ERROR("Assertion failed: ", __VA_ARGS__,\
            "\n\tat line number: ", __LINE__, "\n\tin file: ",\
            __FILE__);\ 
    }
    // TODO - Platform-dependent macro with breakpoint
#else
    #define NRC_ASSERT(cond, ...)
#endif