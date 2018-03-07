
#ifndef __SDLHIDE_MOUSE_H__
#define __SDLHIDE_MOUSE_H__

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

SEXP DLL_EXPORT SDLhide_mouse();

#ifdef __cplusplus
}
#endif

#endif // __SDLHIDE_MOUSE_H__
