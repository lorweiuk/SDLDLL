#include "SDLfill_rect.h"

SEXP DLL_EXPORT SDLfill_rect(SEXP graphicsVec, SEXP x, SEXP y, SEXP w, SEXP h)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    PROTECT( w = coerceVector(w, INTSXP) );
    PROTECT( h = coerceVector(h, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    int out = 0;

    if (INTEGER(x)[0]==0 && INTEGER(y)[0]==0 && INTEGER(w)[0]==0 && INTEGER(h)[0]==0) {
        out = SDL_RenderFillRect(rendererp, 0);
    } else {
        SDL_Rect tempRect;
        tempRect.x = INTEGER(x)[0];
        tempRect.y = INTEGER(y)[0];
        tempRect.w = INTEGER(w)[0];
        tempRect.h = INTEGER(h)[0];
        out = SDL_RenderFillRect(rendererp, &tempRect);
    }

    if (out < 0) {
        Rprintf(SDL_GetError());
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
