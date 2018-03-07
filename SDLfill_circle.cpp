#include "SDLfill_circle.h"

SEXP DLL_EXPORT SDLfill_circle(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( centerx = coerceVector(centerx, INTSXP) );
    PROTECT( centery = coerceVector(centery, INTSXP) );
    PROTECT( radius  = coerceVector(radius, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // make pointers
    int* pcx = INTEGER(centerx);
    int* pcy = INTEGER(centery);

    int x = INTEGER(radius)[0] - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (INTEGER(radius)[0] << 1);

    SDL_Point linepoints[8];

    while (x >= y)
    {
        linepoints[0].x = pcx[0] + x;
        linepoints[0].y = pcy[0] + y;
        linepoints[1].x = pcx[0] - x;
        linepoints[1].y = pcy[0] + y;
        linepoints[2].x = pcx[0] - y;
        linepoints[2].y = pcy[0] + x;
        linepoints[3].x = pcx[0] + y;
        linepoints[3].y = pcy[0] + x;
        linepoints[4].x = pcx[0] - x;
        linepoints[4].y = pcy[0] - y;
        linepoints[5].x = pcx[0] + x;
        linepoints[5].y = pcy[0] - y;
        linepoints[6].x = pcx[0] + y;
        linepoints[6].y = pcy[0] - x;
        linepoints[7].x = pcx[0] - y;
        linepoints[7].y = pcy[0] - x;

        if ( SDL_RenderDrawLines(rendererp, linepoints, 8) < 0) {
            Rprintf( SDL_GetError() );
            return R_NilValue;
        }

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-INTEGER(radius)[0] << 1) + dx;
        }
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
