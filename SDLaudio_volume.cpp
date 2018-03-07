#include "SDLaudio_volume.h"

SEXP DLL_EXPORT SDLaudio_volume(SEXP volume)
{
    // coerce
    PROTECT( volume = coerceVector(volume, INTSXP) );
    // set volume for all channel
    int volumeout = Mix_Volume(-1, INTEGER(volume)[0]);

    SEXP svolout;
    svolout = PROTECT( allocVector(INTSXP, 1));
    INTEGER(svolout)[0] = volumeout;

    UNPROTECT(2);

    return svolout;

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
