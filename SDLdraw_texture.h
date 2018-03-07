
#ifndef __SDLDRAW_TEXTURE_H__
#define __SDLDRAW_TEXTURE_H__

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

SEXP DLL_EXPORT SDLdraw_texture(SEXP graphicsVec, SEXP texturep, SEXP xs, SEXP ys, SEXP ws, SEXP hs, SEXP xd, SEXP yd, SEXP wd, SEXP hd, SEXP angle, SEXP xc, SEXP yc);

#ifdef __cplusplus
}
#endif

#endif // __SDLDRAW_TEXTURE_H__
