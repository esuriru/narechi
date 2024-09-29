#pragma once

#include "core/core.hpp"

#include <string>

namespace narechi::file
{
    class NRC_API nfd_context
    {
    public:
        nfd_context() = default;
        ~nfd_context() = default;

        void init();
        void cleanup();

        void open_file_dialog(std::string& out_path);
        void pick_folder(std::string& out_path);
    };
}