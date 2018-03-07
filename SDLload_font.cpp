#include "SDLload_font.h"

SEXP DLL_EXPORT SDLload_font(SEXP fontname, SEXP textsize)
{
    if (TTF_Init() < 0) {
        Rprintf(TTF_GetError());
        return R_NilValue;
    }
    // coerce
    PROTECT( fontname    = coerceVector(fontname, STRSXP) );
    PROTECT( textsize    = coerceVector(textsize, INTSXP) );
    // load font
    TTF_Font* font = TTF_OpenFont(CHAR( STRING_ELT(fontname, 0)), INTEGER(textsize)[0]);
    if (font == NULL) {
        Rprintf(TTF_GetError());
        return R_NilValue;
    }

    // make external pointer
    SEXP fontout;
    fontout = PROTECT( R_MakeExternalPtr(font, R_NilValue, R_NilValue) );
    R_RegisterCFinalizerEx(fontout, &SDLfinalizerFont, TRUE);

    UNPROTECT(3);

    return fontout;
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
