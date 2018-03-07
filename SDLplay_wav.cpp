#include "SDLplay_wav.h"

SEXP DLL_EXPORT SDLplay_wav(SEXP wavp)
{
    // get wav pointer
    Mix_Chunk* wavin;
    wavin = (Mix_Chunk*) R_ExternalPtrAddr(wavp);
    // play sound, catch error
    if ( Mix_PlayChannel(-1, wavin, 0) < 0 ) {
        Rprintf( SDL_GetError() );
    }

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
