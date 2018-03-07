#include "SDLclose.h"

SEXP DLL_EXPORT SDLclose(SEXP graphicsVec)
{
    // coerce to vecsxp
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP));
    // get external pointers out of graphicsVec
    SDL_Window* windowp     = (SDL_Window*)   R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 0) );
    SDL_Surface* surfacep   = (SDL_Surface*)  R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 1) );
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    SDL_Event* eventp       = (SDL_Event*)    R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 3) );
    SEXP ro                 = PROTECT( VECTOR_ELT(graphicsVec, 6) );
    PROTECT( ro = coerceVector(ro, INTSXP) );

    // reset timer resolution
    SDLreset_timer_resolution(ro);

    delete eventp; // free event structure memory
    SDL_DestroyRenderer(rendererp);
    SDL_FreeSurface(surfacep);
    SDL_DestroyWindow(windowp);

    // set pointers to NULL
    R_ClearExternalPtr( VECTOR_ELT(graphicsVec, 0) );
    R_ClearExternalPtr( VECTOR_ELT(graphicsVec, 1) );
    R_ClearExternalPtr( VECTOR_ELT(graphicsVec, 2) );
    R_ClearExternalPtr( VECTOR_ELT(graphicsVec, 3) );

    SEXP whnull;
    PROTECT( whnull = allocVector(INTSXP,1) );
    INTEGER(whnull)[0] = NA_INTEGER;
    SET_VECTOR_ELT( graphicsVec, 4, whnull );
    SET_VECTOR_ELT( graphicsVec, 5, whnull );

    SDL_Quit();

    UNPROTECT(4);

    return graphicsVec;
}

SEXP DLL_EXPORT SDLclose_audio(SEXP wavp, SEXP wavn)
{
    // first delete audio business
    PROTECT( wavp = coerceVector(wavp, VECSXP) );
    PROTECT( wavn = coerceVector(wavn, INTSXP) );
    // free wav space, clear pointers
    for (int i = 0; i < INTEGER(wavn)[0]; i++) {
        Mix_FreeChunk((Mix_Chunk*) R_ExternalPtrAddr( VECTOR_ELT(wavp, i) ));
        R_ClearExternalPtr( VECTOR_ELT(wavp, i) );
    }
    Mix_CloseAudio();
    Mix_Quit();

    UNPROTECT(2);

    return R_NilValue;
}

SEXP DLL_EXPORT SDLclose_image(SEXP imagep, SEXP imagen)
{
    // first delete audio business
    PROTECT( imagep = coerceVector(imagep, VECSXP) );
    PROTECT( imagen = coerceVector(imagen, INTSXP) );
    // free wav space, clear pointers
    for (int i = 0; i < INTEGER(imagen)[0]; i++) {
        SDL_FreeSurface((SDL_Surface*) R_ExternalPtrAddr( VECTOR_ELT(imagep, i) ));
        R_ClearExternalPtr( VECTOR_ELT(imagep, i) );
    }

    UNPROTECT(2);

    // now call SDLclose() without image
    return R_NilValue;
}

SEXP DLL_EXPORT SDLclose_texture(SEXP texturep, SEXP texturen)
{
    // coerce
    PROTECT( texturep = coerceVector(texturep, VECSXP) );
    PROTECT( texturen = coerceVector(texturen, INTSXP) );
    // call finalizer
    for (int i = 0; i < INTEGER(texturen)[0]; i++) {
        SDLfinalizerTexture(VECTOR_ELT(texturep, i));
    }
    UNPROTECT(2);
    return R_NilValue;
}

SEXP DLL_EXPORT SDLclose_font(SEXP fontp, SEXP fontn) {
    // coerce
    PROTECT( fontp = coerceVector(fontp, VECSXP) );
    PROTECT( fontn = coerceVector(fontn, INTSXP) );
    // call finalizer
    for (int i = 0; i < INTEGER(fontn)[0]; i++) {
        SDLfinalizerFont(VECTOR_ELT(fontp, i));
    }
    UNPROTECT(2);
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
