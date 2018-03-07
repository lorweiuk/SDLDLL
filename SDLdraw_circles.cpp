#include "SDLdraw_circles.h"

SEXP DLL_EXPORT SDLdraw_circles(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius, SEXP n)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( centerx = coerceVector(centerx, INTSXP) );
    PROTECT( centery = coerceVector(centery, INTSXP) );
    PROTECT( radius  = coerceVector(radius, INTSXP) );
    PROTECT( n  = coerceVector(n,  INTSXP) );
    // make pointers
    int* ctx = INTEGER(centerx);
    int* cty = INTEGER(centery);
    int* pn  = INTEGER(n);
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;
    int err = 0;
    SDL_Point circlepoints[8];

    for (int i = 0; i < *pn; ++i) {
        // for every circle

        x = INTEGER(radius)[i] - 1;
        y = 0;
        dx = 1;
        dy = 1;
        err = dx - (INTEGER(radius)[i] << 1);

        while (x >= y)
        {
            circlepoints[0].x = ctx[i] + x;
            circlepoints[0].y = cty[i] + y;
            circlepoints[1].x = ctx[i] + y;
            circlepoints[1].y = cty[i] + x;
            circlepoints[2].x = ctx[i] - y;
            circlepoints[2].y = cty[i] + x;
            circlepoints[3].x = ctx[i] - x;
            circlepoints[3].y = cty[i] + y;
            circlepoints[4].x = ctx[i] - x;
            circlepoints[4].y = cty[i] - y;
            circlepoints[5].x = ctx[i] - y;
            circlepoints[5].y = cty[i] - x;
            circlepoints[6].x = ctx[i] + y;
            circlepoints[6].y = cty[i] - x;
            circlepoints[7].x = ctx[i] + x;
            circlepoints[7].y = cty[i] - y;

            if ( SDL_RenderDrawPoints(rendererp, circlepoints, 8) < 0) {
                Rprintf(SDL_GetError());
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

