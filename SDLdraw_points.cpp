#include "SDLdraw_points.h"

SEXP DLL_EXPORT SDLdraw_points(SEXP graphicsVec, SEXP x, SEXP y, SEXP n)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    PROTECT( n = coerceVector(n, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // set up pointers
    int* px = INTEGER(x);
    int* py = INTEGER(y);
    int* pn = INTEGER(n);
    // set up points to draw
    SDL_Point temppoints[*pn];
    for (int i = 0; i < (*pn); i++) {
        temppoints[i].x = px[i];
        temppoints[i].y = py[i];
    }
    // draw to renderer
    if ( SDL_RenderDrawPoints(rendererp, temppoints, *pn) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(4);

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
