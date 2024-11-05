#pragma once

#define NRC_DECL_EMBED_BYTE_ARRAY(name)      \
    namespace narechi::embed                 \
    {                                        \
        extern const uint8_t name[];         \
        extern const uint32_t name##_length; \
    }

#define NRC_DECL_EMBED_STD_STRING(name) \
    namespace narechi::embed            \
    {                                   \
        extern const std::string name;  \
    }
