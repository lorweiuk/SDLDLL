#include "SDLrender_present_debug.h"

SEXP DLL_EXPORT SDLrender_present_debug(SEXP graphicsVec, SEXP wait, SEXP vert)
{
    //coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );

    // get renderer pointer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    // get timelag
    SEXP lagtime     = PROTECT( VECTOR_ELT(graphicsVec, 7) );
    PROTECT( lagtime = coerceVector(lagtime, INTSXP) );

    // get wait
    SEXP waitp = PROTECT( coerceVector(wait, INTSXP) );
    // get vert
    SEXP vertp = PROTECT( coerceVector(vert, INTSXP) );

    // present renderer
    int out = SDL_RenderPresent(rendererp, INTEGER(waitp)[0], INTEGER(vertp)[0]);
    SEXP outp = PROTECT( allocVector(INTSXP, 1) );
    INTEGER(outp)[0] = out;

    //int time = SDL_GetTicks();
    // timestamp changed to windows api tickcount because event timestamp is also this counter now
    int time = timeGetTime();

    // allocate R integer
    SEXP timeout = PROTECT( allocVector(INTSXP, 1) );
    INTEGER(timeout)[0] = time + INTEGER(lagtime)[0];

    // if !wait, note down timeout
    if (INTEGER(waitp)[0] == 0) {
        PROTECT( SET_VECTOR_ELT(graphicsVec, 9, timeout) );
    }
    PROTECT( SET_VECTOR_ELT(graphicsVec, 10, timeout) );

    if (INTEGER(waitp)[0] == 0) {
        //UNPROTECT(8);
        UNPROTECT(9);
    } else {
        //UNPROTECT(13);
        UNPROTECT(8);
    }

    return outp;
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
