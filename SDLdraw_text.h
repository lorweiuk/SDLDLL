
#ifndef __SDLDRAW_TEXT_H__
#define __SDLDRAW_TEXT_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_ttf.h"

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

SEXP DLL_EXPORT SDLdraw_text(SEXP graphicsVec, SEXP fontp, SEXP text, SEXP x, SEXP y);

#ifdef __cplusplus
}
#endif

#endif // __SDLDRAW_TEXT_H__
