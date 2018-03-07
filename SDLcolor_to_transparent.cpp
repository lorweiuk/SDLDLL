#include "SDLcolor_to_transparent.h"

SEXP DLL_EXPORT SDLcolor_to_transparent(SEXP surfacep, SEXP rin, SEXP gin, SEXP bin)
{
    // coerce
    PROTECT( rin = coerceVector(rin, INTSXP) );
    PROTECT( gin = coerceVector(gin, INTSXP) );
    PROTECT( bin = coerceVector(bin, INTSXP) );
    // get renderer
    SDL_Surface* tempsurface = (SDL_Surface*) R_ExternalPtrAddr( surfacep );

    if ( SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, INTEGER(rin)[0], INTEGER(gin)[0], INTEGER(bin)[0])) < 0) {
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
