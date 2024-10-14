#include "file/nfd_context.hpp"

#include "core/logger.hpp"

#include "nfd.hpp"

namespace narechi::file
{
    void nfd_context::init()
    {
        NFD_Init();
    }

    void nfd_context::cleanup()
    {
        NFD_Quit();
    }

    std::optional<std::string> nfd_context::open_file_dialog()
    {
        NFD::UniquePath nfd_out_path = nullptr;
        nfdresult_t result = NFD::OpenDialog(nfd_out_path);

        if (result == NFD_OKAY)
        {
            return std::make_optional(std::string(nfd_out_path.get()));
        }
        else if (result == NFD_ERROR)
        {
            NRC_CORE_FATAL("NFDe Error: ", NFD::GetError());
        }

        return std::nullopt;
    }

    std::optional<std::string> nfd_context::pick_folder()
    {
        NFD::UniquePath nfd_out_path = nullptr;
        nfdresult_t result = NFD::PickFolder(nfd_out_path);

        if (result == NFD_OKAY)
        {
            return std::make_optional(std::string(nfd_out_path.get()));
        }
        else if (result == NFD_ERROR)
        {
            NRC_CORE_FATAL("NFDe Error: ", NFD::GetError());
        }

        return std::nullopt;
    }
}