
#ifndef __SDLDRAW_CIRCLE_H__
#define __SDLDRAW_CIRCLE_H__

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

SEXP DLL_EXPORT SDLdraw_circle(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius);

#ifdef __cplusplus
}
#endif

#endif // __SDLDRAW_CIRCLE_H__
