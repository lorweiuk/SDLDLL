
#ifndef __SDLDRAW_IMAGE_H__
#define __SDLDRAW_IMAGE_H__

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

SEXP DLL_EXPORT SDLdraw_image(SEXP graphicsVec, SEXP imagep, SEXP x, SEXP y, SEXP w, SEXP h);

#ifdef __cplusplus
}
#endif

#endif // __SDLDRAW_IMAGE_H__
