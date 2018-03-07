#include "SDLinit_audio.h"

SEXP DLL_EXPORT SDLinit_audio()
{
    if (SDL_WasInit(SDL_INIT_AUDIO) != 0) {
        Mix_Quit();
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
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
