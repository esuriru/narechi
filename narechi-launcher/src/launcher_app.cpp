#include "narechi.h" 

#include "entry.cpp"

namespace narechi
{
    __declspec(dllimport) narechi::app* narechi::create_app();
}

// TODO:
// https://www.youtube.com/watch?v=88dmtleVywk&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=11
// TODO:
// https://stackoverflow.com/questions/594703/exporting-class-from-executable-to-dll?rq=4

class launcher_app : public narechi::app 
{
public:
    launcher_app() = default;

};

narechi::app* narechi::create_app()
{
    return new launcher_app();
}