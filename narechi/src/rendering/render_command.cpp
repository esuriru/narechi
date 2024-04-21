#include "render_command.hpp"

namespace narechi
{
    uptr<renderer_api> render_command::renderer_api = renderer_api::create();
}