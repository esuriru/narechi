#pragma once

#define NRC_DECL_EMBED_BYTE_ARRAY(name)      \
    namespace narechi::embed                 \
    {                                        \
        extern const uint8_t name[];         \
        extern const uint32_t name##_length; \
    }
