

#ifndef __SDLRENDER_PRESENT_DEBUG_H__
#define __SDLRENDER_PRESENT_DEBUG_H__

#include <windows.h>
#include <cmath>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>

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

SEXP DLL_EXPORT SDLrender_present_debug(SEXP graphicsVec, SEXP wait, SEXP vert);

#ifdef __cplusplus
}
#endif

#endif // __SDLRENDER_PRESENT_DEBUG_H__
