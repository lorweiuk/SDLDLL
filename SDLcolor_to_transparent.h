
#ifndef __SDLCOLOR_TO_TRANSPARENT_H__
#define __SDLCOLOR_TO_TRANSPARENT_H__

#include <windows.h>
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

SEXP DLL_EXPORT SDLcolor_to_transparent(SEXP surfacep, SEXP rin, SEXP gin, SEXP bin);

#ifdef __cplusplus
}
#endif

#endif // __SDLCOLOR_TO_TRANSPARENT_H__
