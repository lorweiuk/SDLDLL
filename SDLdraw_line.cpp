#include "SDLdraw_line.h"

SEXP DLL_EXPORT SDLdraw_line(SEXP graphicsVec, SEXP x1, SEXP y1, SEXP x2, SEXP y2)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x1 = coerceVector(x1, INTSXP) );
    PROTECT( x2 = coerceVector(x2, INTSXP) );
    PROTECT( y1 = coerceVector(y1, INTSXP) );
    PROTECT( y2 = coerceVector(y2, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // draw line
    if ( SDL_RenderDrawLine(rendererp, INTEGER(x1)[0], INTEGER(y1)[0], INTEGER(x2)[0], INTEGER(y2)[0]) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(5);

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
