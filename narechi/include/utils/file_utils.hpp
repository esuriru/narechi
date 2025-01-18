#pragma once

#include "core/core.hpp"
#include "file/nfd_context.hpp"

#include <optional>
#include <string>
#include <filesystem>

namespace narechi::utils::file
{
    NRC_API std::optional<std::string> open_file_dialog(
        const ::narechi::file::open_file_dialog_args& args = {});
    NRC_API std::optional<std::string> pick_folder();
    NRC_API void open_explorer_in_dir(const std::filesystem::path& path);
    NRC_API std::string open_file_as_string(const std::filesystem::path& path);
}