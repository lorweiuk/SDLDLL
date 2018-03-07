
#ifndef __SDLCLOSE_FONT_H__
#define __SDLCLOSE_FONT_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_ttf.h"
#include "SDLfinalizer.h"

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

SEXP DLL_EXPORT SDLclose_font(SEXP font);

#ifdef __cplusplus
}
#endif

#endif // __SDLCLOSE_FONT_H__
