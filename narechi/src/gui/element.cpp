#include "gui/element.hpp"

#include "uuid.h"

namespace narechi::gui
{
    element::element()
    {
        generate_uid();
    }

    void element::generate_uid()
    {
        uid = uuids::to_string(uuids::uuid_system_generator {}());
    }

    void element::set_custom_uid(const std::string& uid)
    {
        this->uid = uid;
    }
}