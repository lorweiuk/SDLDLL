#include "SDLdraw_image.h"

SEXP DLL_EXPORT SDLdraw_image(SEXP graphicsVec, SEXP imagep, SEXP x, SEXP y, SEXP w, SEXP h)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    PROTECT( w = coerceVector(w, INTSXP) );
    PROTECT( h = coerceVector(h, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // get surfacep from imagep
    SDL_Surface* surfacep = (SDL_Surface*) R_ExternalPtrAddr( imagep );
    // prepare drawing
    SDL_Rect temprect;
    temprect.x = INTEGER(x)[0];
    temprect.y = INTEGER(y)[0];
    temprect.w = INTEGER(w)[0];
    temprect.h = INTEGER(h)[0];
    SDL_Texture* temptexture = SDL_CreateTextureFromSurface(rendererp, surfacep);
    if (temptexture == NULL) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }
    // draw to renderer
    if ( SDL_RenderCopy(rendererp, temptexture, NULL, &temprect ) < 0) {
        Rprintf( SDL_GetError() );
    }
    SDL_DestroyTexture(temptexture);

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
