#include "SDLfill_circles.h"

SEXP DLL_EXPORT SDLfill_circles(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius, SEXP n)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( centerx = coerceVector(centerx, INTSXP) );
    PROTECT( centery = coerceVector(centery, INTSXP) );
    PROTECT( radius  = coerceVector(radius, INTSXP) );
    PROTECT( n  = coerceVector(n,  INTSXP) );
    // make pointers
    int* pcx = INTEGER(centerx);
    int* pcy = INTEGER(centery);
    int* pn  = INTEGER(n);
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;
    int err = 0;
    SDL_Point linepoints[8];

    for (int i = 0; i < *pn; ++i) {
        // for every circle

        x = INTEGER(radius)[i] - 1;
        y = 0;
        dx = 1;
        dy = 1;
        err = dx - (INTEGER(radius)[i] << 1);

        linepoints[8];

        while (x >= y)
        {
            linepoints[0].x = pcx[i] + x;
            linepoints[0].y = pcy[i] + y;
            linepoints[1].x = pcx[i] - x;
            linepoints[1].y = pcy[i] + y;
            linepoints[2].x = pcx[i] - y;
            linepoints[2].y = pcy[i] + x;
            linepoints[3].x = pcx[i] + y;
            linepoints[3].y = pcy[i] + x;
            linepoints[4].x = pcx[i] - x;
            linepoints[4].y = pcy[i] - y;
            linepoints[5].x = pcx[i] + x;
            linepoints[5].y = pcy[i] - y;
            linepoints[6].x = pcx[i] + y;
            linepoints[6].y = pcy[i] - x;
            linepoints[7].x = pcx[i] - y;
            linepoints[7].y = pcy[i] - x;

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
                err += (-INTEGER(radius)[i] << 1) + dx;
            }
        }
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

