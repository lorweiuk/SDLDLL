#include "SDLfill_rects.h"

SEXP DLL_EXPORT SDLfill_rects(SEXP graphicsVec, SEXP x, SEXP y, SEXP w, SEXP h, SEXP n)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    PROTECT( w = coerceVector(w, INTSXP) );
    PROTECT( h = coerceVector(h, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    SDL_Rect temprects[INTEGER(n)[0]];
    for (int i = 0; i < INTEGER(n)[0]; i++) {
        temprects[i].x = INTEGER(x)[i];
        temprects[i].y = INTEGER(y)[i];
        temprects[i].w = INTEGER(w)[i];
        temprects[i].h = INTEGER(h)[i];
    }

    if ( SDL_RenderFillRects(rendererp, temprects, INTEGER(n)[0]) < 0) {
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
