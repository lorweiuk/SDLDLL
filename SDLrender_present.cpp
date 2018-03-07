#include "SDLrender_present.h"

SEXP DLL_EXPORT SDLrender_present(SEXP graphicsVec, SEXP wait, SEXP vert)
{
    //coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );

    // get renderer pointer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    // get timelag
    SEXP lagtime     = PROTECT( VECTOR_ELT(graphicsVec, 7) );
    PROTECT( lagtime = coerceVector(lagtime, INTSXP) );

    // get wait
    PROTECT( wait = coerceVector(wait, INTSXP) );
    int waitp = INTEGER(wait)[0];

    // get vert (interval_one flag)
    PROTECT( vert = coerceVector(vert, INTSXP) );
    int vertp = INTEGER(vert)[0];

    // present renderer
    // when waiting, middlerefresh is center-time of refresh
    // otherwise 0
    int middlerefresh = SDL_RenderPresent(rendererp, waitp, vertp);

    // timestamp changed to windows api tickcount because event timestamp is also this counter now
    int time = timeGetTime();

    // allocate R integer
    SEXP timeout = PROTECT( allocVector(INTSXP, 1) );

    // set timeout depending on wait
    if (waitp == 1) {
        INTEGER(timeout)[0] = middlerefresh + INTEGER(lagtime)[0];
    } else if (waitp == 0) {
        INTEGER(timeout)[0] = time + INTEGER(lagtime)[0];
    }

    // if !wait, note down timeout
    if (waitp == 0) {
        PROTECT( SET_VECTOR_ELT(graphicsVec, 9, timeout) );
    }
    PROTECT( SET_VECTOR_ELT(graphicsVec, 10, timeout) );

    if (waitp == 0) {
        UNPROTECT(8);
    } else {
        UNPROTECT(7);
    }

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
