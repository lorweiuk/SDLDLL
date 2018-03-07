#include "SDLset_timer_resolution.h"

SEXP DLL_EXPORT SDLset_timer_resolution(SEXP resin)
{
    // coerce to right type
    PROTECT( resin = coerceVector(resin, INTSXP) );

    TIMECAPS tc;    // holds minimum and maximum timer res
    UINT     wTimerRes;

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
        Rprintf("Error querying windows timer resolution. Resolution cannot be set.");
        UNPROTECT(1);
        return R_NilValue;
    }

    wTimerRes = min( max(tc.wPeriodMin, INTEGER(resin)[0]), tc.wPeriodMax );
    timeBeginPeriod(wTimerRes);

    SEXP resout        = PROTECT( allocVector(INTSXP, 1));
    INTEGER(resout)[0] = wTimerRes;

    UNPROTECT(2);

    return resout;
}


SEXP DLL_EXPORT SDLreset_timer_resolution(SEXP resin)
{
    // coerce to right type
    PROTECT( resin = coerceVector(resin, INTSXP) );

    timeEndPeriod( INTEGER(resin)[0] );

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
