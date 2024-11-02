#pragma once

#include "core/core.hpp"

#include <optional>
#include <string>

namespace narechi::utils::file
{
    NRC_API std::optional<std::string> open_file_dialog();
    NRC_API std::optional<std::string> pick_folder();
}