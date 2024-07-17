#include "core/window.hpp"
#include "core/logger.hpp"

#include "platform/win32/win32window.hpp"

namespace narechi
{
    uptr<window> window::create(const window_properties& properties)
    {
#ifdef NRC_PLATFORM_WINDOWS
        return make_uptr<win32window>(properties);
#else
        NRC_CORE_FATAL("Could not create a window: unsupported platform");
#endif
    }
}
