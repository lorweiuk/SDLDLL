#include "SDLdraw_circle.h"

SEXP DLL_EXPORT SDLdraw_circle(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( centerx = coerceVector(centerx, INTSXP) );
    PROTECT( centery = coerceVector(centery, INTSXP) );
    PROTECT( radius  = coerceVector(radius, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // make pointers
    int* ctx = INTEGER(centerx);
    int* cty = INTEGER(centery);

    int x = INTEGER(radius)[0] - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (INTEGER(radius)[0] << 1);

    SDL_Point circlepoints[8];

    while (x >= y)
    {
        circlepoints[0].x = ctx[0] + x;
        circlepoints[0].y = cty[0] + y;
        circlepoints[1].x = ctx[0] + y;
        circlepoints[1].y = cty[0] + x;
        circlepoints[2].x = ctx[0] - y;
        circlepoints[2].y = cty[0] + x;
        circlepoints[3].x = ctx[0] - x;
        circlepoints[3].y = cty[0] + y;
        circlepoints[4].x = ctx[0] - x;
        circlepoints[4].y = cty[0] - y;
        circlepoints[5].x = ctx[0] - y;
        circlepoints[5].y = cty[0] - x;
        circlepoints[6].x = ctx[0] + y;
        circlepoints[6].y = cty[0] - x;
        circlepoints[7].x = ctx[0] + x;
        circlepoints[7].y = cty[0] - y;

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
