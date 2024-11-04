#include "graphics/render_command.hpp"

namespace narechi::graphics
{
    uptr<renderer_api> render_command::renderer_api = renderer_api::create();
}