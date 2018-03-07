#include "SDLdraw_point.h"

SEXP DLL_EXPORT SDLdraw_point(SEXP graphicsVec, SEXP x, SEXP y)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // render point
    if ( SDL_RenderDrawPoint(rendererp, INTEGER(x)[0], INTEGER(y)[0]) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(3);

    return R_NilValue;
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
