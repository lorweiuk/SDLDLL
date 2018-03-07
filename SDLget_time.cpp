#include "SDLget_time.h"

SEXP DLL_EXPORT SDLget_time(SEXP graphicsVec)
{
    //coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    // add timelag
    SEXP lagtime     = PROTECT( VECTOR_ELT(graphicsVec, 7) );
    PROTECT( lagtime = coerceVector(lagtime, INTSXP) );

    // allocate space
    SEXP timeout;
    timeout = PROTECT( allocVector(INTSXP, 1) );

    //INTEGER(timeout)[0] = SDL_GetTicks();
    // changed to windows api tickcounter (because event timestamps were also changed to this counter)
    INTEGER(timeout)[0] = timeGetTime() + INTEGER(lagtime)[0];

    UNPROTECT(4);

    return timeout;
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
