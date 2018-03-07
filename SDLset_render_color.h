
#ifndef __SDLSET_RENDER_COLOR_H__
#define __SDLSET_RENDER_COLOR_H__

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

SEXP DLL_EXPORT SDLset_render_color(SEXP graphicsVec, SEXP r, SEXP g, SEXP b, SEXP a);

#ifdef __cplusplus
}
#endif

#endif // __SDLSET_RENDER_COLOR_H__
