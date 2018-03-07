#include "SDLdraw_texture.h"

SEXP DLL_EXPORT SDLdraw_texture(SEXP graphicsVec, SEXP texturep, SEXP xs, SEXP ys, SEXP ws, SEXP hs, SEXP xd, SEXP yd, SEXP wd, SEXP hd, SEXP angle, SEXP xc, SEXP yc)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( xs = coerceVector(xs, INTSXP) );
    PROTECT( ys = coerceVector(ys, INTSXP) );
    PROTECT( ws = coerceVector(ws, INTSXP) );
    PROTECT( hs = coerceVector(hs, INTSXP) );
    PROTECT( xd = coerceVector(xd, INTSXP) );
    PROTECT( yd = coerceVector(yd, INTSXP) );
    PROTECT( wd = coerceVector(wd, INTSXP) );
    PROTECT( hd = coerceVector(hd, INTSXP) );
    PROTECT( angle = coerceVector(angle, REALSXP) );
    PROTECT( xc = coerceVector(xc, INTSXP) );
    PROTECT( yc = coerceVector(yc, INTSXP) );
    // get renderer and texture
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    SDL_Texture*  temptext  = (SDL_Texture*)  R_ExternalPtrAddr( texturep );
    // prepare drawing rects
    SDL_Rect srect;
    srect.x = INTEGER(xs)[0];
    srect.y = INTEGER(ys)[0];
    srect.w = INTEGER(ws)[0];
    srect.h = INTEGER(hs)[0];

    SDL_Rect drect;
    drect.x = INTEGER(xd)[0];
    drect.y = INTEGER(yd)[0];
    drect.w = INTEGER(wd)[0];
    drect.h = INTEGER(hd)[0];

    SDL_Point cpoint;
    cpoint.x = INTEGER(xc)[0];
    cpoint.y = INTEGER(yc)[0];

    // copy texture
    int out = 0;

           if ( (srect.x == 0 && srect.y == 0 && srect.w == 0 && srect.h == 0) && (drect.x == 0 && drect.y == 0 && drect.w == 0 && drect.h == 0) ) {
        out = SDL_RenderCopyEx(rendererp, temptext, NULL, NULL, REAL(angle)[0], &cpoint, SDL_FLIP_NONE );

    } else if ( (srect.x == 0 && srect.y == 0 && srect.w == 0 && srect.h == 0) && (drect.x != 0 && drect.y != 0 && drect.w != 0 && drect.h != 0) ) {
        out = SDL_RenderCopyEx(rendererp, temptext, NULL, &drect, REAL(angle)[0], &cpoint, SDL_FLIP_NONE );

    } else if ( (srect.x != 0 && srect.y != 0 && srect.w != 0 && srect.h != 0) && (drect.x == 0 && drect.y == 0 && drect.w == 0 && drect.h == 0) ) {
        out = SDL_RenderCopyEx(rendererp, temptext, &srect, NULL, REAL(angle)[0], &cpoint, SDL_FLIP_NONE );

    } else if ( (srect.x != 0 && srect.y != 0 && srect.w != 0 && srect.h != 0) && (drect.x != 0 && drect.y != 0 && drect.w != 0 && drect.h != 0) ) {
        out = SDL_RenderCopyEx(rendererp, temptext, &srect, &drect, REAL(angle)[0], &cpoint, SDL_FLIP_NONE );
    }

    if (out < 0) {
        Rprintf(SDL_GetError());
    }

    UNPROTECT(12);

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

