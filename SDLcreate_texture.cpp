#include "SDLcreate_texture.h"

SEXP DLL_EXPORT SDLcreate_texture(SEXP graphicsVec, SEXP w, SEXP h)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( w = coerceVector(w, INTSXP) );
    PROTECT( h = coerceVector(h, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // create texture
    SDL_Texture* temptexture = SDL_CreateTexture(rendererp, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET, INTEGER(w)[0], INTEGER(h)[0]);

    if (temptexture == NULL) {
        Rprintf( SDL_GetError() );
    }
    // allow alpha for texture (thus, alpha channel use is default for textures)
    if (SDL_SetTextureBlendMode(temptexture, SDL_BLENDMODE_BLEND) < 0) {
        Rprintf( SDL_GetError() );
    }

    // make external pointer
    SEXP textureout;
    textureout = PROTECT( R_MakeExternalPtr(temptexture, R_NilValue, R_NilValue) );
    R_RegisterCFinalizerEx(textureout, &SDLfinalizerTexture, TRUE);

    UNPROTECT(4);

    return textureout;
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
