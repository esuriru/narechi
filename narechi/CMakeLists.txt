set(NARECHI_SOURCES
    "src/entry.cpp"
    "src/narechi.h"

    "src/core/assert.hpp"
    "src/core/core.hpp"

    "src/core/logger.hpp"
    "src/core/logger.cpp"

    "src/core/app.hpp"
    "src/core/app.cpp"

    "src/core/buffer.hpp"

    "src/rendering/buffer.hpp"
    "src/rendering/shader_type.hpp"

    "src/utils/time_utils.hpp"
    "src/utils/time_utils.cpp"
)

add_library(narechi-engine SHARED ${NARECHI_SOURCES})

target_include_directories(narechi-engine PUBLIC "src")

if (WIN32)
    message("windows")
    target_compile_definitions(narechi-engine PUBLIC 
        "NRC_PLATFORM_WINDOWS;NRC_DEBUG;")
else()
    message("not windows")
endif()