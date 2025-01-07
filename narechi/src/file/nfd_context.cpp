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

    std::optional<std::string> nfd_context::open_file_dialog(
        const open_file_dialog_args& args)
    {
        NFD::UniquePath nfd_out_path = nullptr;

        nfdresult_t result;
        if (args.filters.empty())
        {
            result = NFD::OpenDialog(nfd_out_path);
        }
        else
        {
            std::vector<nfdfilteritem_t> filter_items {};
            for (auto& filter : args.filters)
            {
                filter_items.push_back(
                    { filter.first.c_str(), filter.second.c_str() });
            }

            result = NFD::OpenDialog(
                nfd_out_path, filter_items.data(), filter_items.size());
        }

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