#include "SDLentroduce.h"
#include "SDLopen.h"
#include "SDLwait.h"

void DLL_EXPORT SDLentroduce()
{
    int winp;
    int rendp;
    int surfp;
    int eventp;
    int wout;
    int hout;
    int ms = 3000;
    const char* err[100];

    SDLopen(0, 0, 0, 0, &winp, &surfp, &rendp, &eventp, &wout, &hout, err );

    int timeout;
    SDLwait(&ms, &timeout);
}
/*extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
}*/

