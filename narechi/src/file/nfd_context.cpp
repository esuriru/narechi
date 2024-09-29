#include "file/nfd_context.hpp"

#include "nfd.h"

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

    void nfd_context::open_file_dialog(std::string& out_path)
    {
        nfdu8char_t* buf;
        nfdopendialogu8args_t args { .filterCount = 0 };
        NFD_OpenDialogU8_With(&buf, &args);
        out_path = buf;
    }

    void nfd_context::pick_folder(std::string& out_path)
    {
        nfdu8char_t* buf;
        nfdpickfolderu8args_t args {};
        NFD_PickFolderU8_With(&buf, &args);
        out_path = buf;
    }
}