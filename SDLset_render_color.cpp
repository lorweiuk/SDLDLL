#include "SDLset_render_color.h"

SEXP DLL_EXPORT SDLset_render_color(SEXP graphicsVec, SEXP r, SEXP g, SEXP b, SEXP a)
{
    // coerce to list
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    // get renderer address
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // coerce integer
    PROTECT( r = coerceVector(r,INTSXP) );
    PROTECT( g = coerceVector(g,INTSXP) );
    PROTECT( b = coerceVector(b,INTSXP) );
    PROTECT( a = coerceVector(a,INTSXP) );
    // set renderer color
    if ( SDL_SetRenderDrawColor(rendererp, INTEGER(r)[0], INTEGER(g)[0], INTEGER(b)[0], INTEGER(a)[0]) < 0 ) {
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
