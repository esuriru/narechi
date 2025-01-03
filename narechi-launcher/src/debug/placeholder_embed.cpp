#include <cstdint>

namespace narechi::embed
{
    extern const uint8_t libnarechi_engine[] = {};
    extern const uint32_t libnarechi_engine_length
        = sizeof(libnarechi_engine) / sizeof(uint8_t);

    extern const uint8_t narechi_player[] = {};
    extern const uint32_t narechi_player_length
        = sizeof(narechi_player) / sizeof(uint8_t);
}