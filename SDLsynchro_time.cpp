#include "SDLsynchro_time.h"

using namespace std::chrono;


SEXP DLL_EXPORT SDLsynchro_time()
{
    // allocate space
    SEXP timeout_sdl, timeout_chrono, timeout_wintick, timeout_wintime;
    timeout_sdl     = PROTECT( allocVector(INTSXP, 1) );
    timeout_chrono  = PROTECT( allocVector(INTSXP, 1) );
    timeout_wintick = PROTECT( allocVector(INTSXP, 1) );
    timeout_wintime = PROTECT( allocVector(INTSXP, 1) );

    INTEGER(timeout_sdl)[0]     = SDL_GetTicks();
    INTEGER(timeout_chrono)[0]  = duration_cast<milliseconds>( system_clock::now().time_since_epoch() ).count();
    INTEGER(timeout_wintick)[0] = GetTickCount();
    INTEGER(timeout_wintime)[0] = timeGetTime();

    // put outputs into list
    SEXP timevec;
    timevec = PROTECT( allocVector(VECSXP, 4) );
    PROTECT( SET_VECTOR_ELT(timevec, 0, timeout_sdl) );
    PROTECT( SET_VECTOR_ELT(timevec, 1, timeout_chrono) );
    PROTECT( SET_VECTOR_ELT(timevec, 2, timeout_wintick) );
    PROTECT( SET_VECTOR_ELT(timevec, 3, timeout_wintime) );

    UNPROTECT(9);

    return timevec;
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
