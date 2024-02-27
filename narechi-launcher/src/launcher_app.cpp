#include "narechi.h" 

class launcher_app : narechi::app 
{
    narechi::app* create_app()
    {
        return new launcher_app();
    }
};