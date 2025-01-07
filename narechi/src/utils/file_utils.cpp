#include "utils/file_utils.hpp"

#include "core/assert.hpp"
#include "file/nfd_context.hpp"

extern narechi::file::nfd_context* get_nfd_ctx();

namespace narechi::utils::file
{
    std::optional<std::string> open_file_dialog(
        const ::narechi::file::open_file_dialog_args& args)
    {
        NRC_ASSERT(get_nfd_ctx(), "nfde context unavailable");
        return get_nfd_ctx()->open_file_dialog(args);
    }

    std::optional<std::string> pick_folder()
    {
        NRC_ASSERT(get_nfd_ctx(), "nfde context unavailable");
        return get_nfd_ctx()->pick_folder();
    }

    void open_explorer_in_dir(const std::filesystem::path& path)
    {
#ifdef NRC_PLATFORM_WINDOWS
        std::string command = "explorer ";
        command = command + path.string();
        system(command.c_str());
#endif
    }
}
