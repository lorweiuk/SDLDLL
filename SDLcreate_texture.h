
#ifndef __SDLCREATE_TEXTURE_H__
#define __SDLCREATE_TEXTURE_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
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

SEXP DLL_EXPORT SDLcreate_texture(SEXP graphicsVec, SEXP w, SEXP h);

#ifdef __cplusplus
}
#endif

#endif // __SDLCREATE_TEXTURE_H__
