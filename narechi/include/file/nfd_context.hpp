#pragma once

#include "core/core.hpp"

#include <string>
#include <optional>

namespace narechi::file
{
    class NRC_API nfd_context
    {
    public:
        nfd_context() = default;
        ~nfd_context() = default;

        void init();
        void cleanup();

        std::optional<std::string> open_file_dialog();
        std::optional<std::string> pick_folder();
    };
}