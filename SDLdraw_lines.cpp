#include "SDLdraw_lines.h"

SEXP DLL_EXPORT SDLdraw_lines(SEXP graphicsVec, SEXP x1, SEXP y1, SEXP x2, SEXP y2, SEXP n)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x1 = coerceVector(x1, INTSXP) );
    PROTECT( x2 = coerceVector(x2, INTSXP) );
    PROTECT( y1 = coerceVector(y1, INTSXP) );
    PROTECT( y2 = coerceVector(y2, INTSXP) );
    PROTECT( n  = coerceVector(n,  INTSXP) );
    // make pointers
    int* px1 = INTEGER(x1);
    int* px2 = INTEGER(x2);
    int* py1 = INTEGER(y1);
    int* py2 = INTEGER(y2);
    int* pn  = INTEGER(n);
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    SDL_Point linepoints[(*pn)*2];
    for (int i = 0; i < (*pn); i++) {
        linepoints[i*2+0].x = px1[i];
        linepoints[i*2+0].y = py1[i];
        linepoints[i*2+1].x = px2[i];
        linepoints[i*2+1].y = py2[i];
    }
    // draw to renderer
    if ( SDL_RenderDrawLines(rendererp, linepoints, *pn) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(6);

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
