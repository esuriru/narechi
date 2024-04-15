#include <narechi.hpp> 

// TODO:
// https://www.youtube.com/watch?v=88dmtleVywk&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=11
// TODO:
// https://stackoverflow.com/questions/594703/exporting-class-from-executable-to-dll?rq=4

namespace narechi
{
    class launcher_app : public narechi::app 
    {
    public:
        launcher_app() = default;

    };

    app* create_app()
    {
        return new launcher_app();
    }
}
