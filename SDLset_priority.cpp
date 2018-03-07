#include "SDLset_priority.h"

SEXP DLL_EXPORT SDLset_priority(SEXP priority) {
    // sets priority ON WINDOWS
    // not portable
    PROTECT( priority = coerceVector(priority, INTSXP) );

    DWORD dwPriClass;

    switch(INTEGER(priority)[0]) {
    case 0:
        if (!SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)) {
            Rprintf("Failed to enter priority NORMAL_PRIORITY_CLASS");
        }
        break;
    case 1:
        if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
            Rprintf("Failed to enter priority HIGH_PRIORITY_CLASS");
        }
        break;
    case 2:
        if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS)) {
            Rprintf("Failed to enter priority REALTIME_PRIORITY_CLASS");
        }
        break;
    }

    UNPROTECT(1);

    return R_NilValue;
}
