#include "SDLload_wav.h"

SEXP DLL_EXPORT SDLload_wav(SEXP wavfile)
{
    // coerce
    PROTECT( wavfile = coerceVector(wavfile, STRSXP) );
    // load wav
    Mix_Chunk* wav = Mix_LoadWAV( CHAR(STRING_ELT(wavfile, 0)) );

    if (wav == NULL){
        Rprintf(SDL_GetError());
        return R_NilValue;
    }
    // make external pointer
    SEXP extwav = PROTECT( R_MakeExternalPtr(wav, R_NilValue, R_NilValue) );
    // register finalizer
    R_RegisterCFinalizerEx(extwav, &SDLfinalizerWav, TRUE);

    UNPROTECT(2);

    return extwav;
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
