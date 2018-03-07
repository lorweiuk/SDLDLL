
#ifndef __SDLOPEN_H__
#define __SDLOPEN_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include <cmath>
#include "SDLset_timer_resolution.h"

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

SEXP DLL_EXPORT SDLopen(SEXP x, SEXP y, SEXP w, SEXP h);

#ifdef __cplusplus
}
#endif

#endif // __SDLOPEN_H__
