#pragma once

#include "core/core.hpp"

#include <string>
#include <optional>
#include <vector>

namespace narechi::file
{
    struct NRC_API open_file_dialog_args
    {
        std::vector<std::pair<std::string, std::string>> filters {};
    };

    class NRC_API nfd_context
    {
    public:
        nfd_context() = default;
        ~nfd_context() = default;

        void init();
        void cleanup();

        std::optional<std::string> open_file_dialog(const open_file_dialog_args& args);
        std::optional<std::string> pick_folder();
    };
}