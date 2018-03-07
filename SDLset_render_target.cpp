#include "SDLset_render_target.h"

SEXP DLL_EXPORT SDLset_render_target_texture(SEXP graphicsVec, SEXP texturep)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    // get texture pointer
    SDL_Texture* temptext   = (SDL_Texture*) R_ExternalPtrAddr(texturep);
    // get renderer pointer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );

    // change render target
    if ( SDL_SetRenderTarget(rendererp, temptext) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(1);

    return R_NilValue;
}

SEXP DLL_EXPORT SDLset_render_target_reset(SEXP graphicsVec)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    // get renderer pointer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // change render target
    if ( SDL_SetRenderTarget(rendererp, NULL) < 0) {
        Rprintf( SDL_GetError() );
    }

    UNPROTECT(1);

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
