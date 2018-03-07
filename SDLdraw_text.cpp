#include "SDLdraw_text.h"

SEXP DLL_EXPORT SDLdraw_text(SEXP graphicsVec, SEXP fontp, SEXP text, SEXP x, SEXP y)
{
    // coerce
    PROTECT( graphicsVec = coerceVector(graphicsVec, VECSXP) );
    PROTECT( text = coerceVector(text, STRSXP) );
    PROTECT( x    = coerceVector(x, INTSXP) );
    PROTECT( y    = coerceVector(y, INTSXP) );
    // get renderer
    SDL_Renderer* rendererp = (SDL_Renderer*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 2) );
    // get fontpointer
    TTF_Font* tempfontp = NULL;
    tempfontp = (TTF_Font*) R_ExternalPtrAddr( fontp );

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    // get current renderer color
    if ( SDL_GetRenderDrawColor(rendererp, &r, &g, &b, &a) < 0) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }
    // draw to surface
    SDL_Color tempcolor;
    tempcolor.r = r;
    tempcolor.g = g;
    tempcolor.b = b;
    tempcolor.a = a;
    SDL_Surface* textSurface = TTF_RenderText_Solid(tempfontp, CHAR(STRING_ELT(text,0)), tempcolor);
    if (textSurface==NULL) {
        Rprintf(SDL_GetError());
        return R_NilValue;
    }
    // draw to renderer
    SDL_Rect textRect;
    textRect.x = INTEGER(x)[0];
    textRect.y = INTEGER(y)[0];
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendererp, textSurface);
    if (textTexture == NULL) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }
    SDL_FreeSurface(textSurface);
    if ( SDL_RenderCopy(rendererp, textTexture, NULL, &textRect) < 0) {
        Rprintf(SDL_GetError());
    }
    SDL_DestroyTexture(textTexture);

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
