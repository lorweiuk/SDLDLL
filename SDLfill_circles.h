

#ifndef __SDLFILL_CIRCLES_H__
#define __SDLFILL_CIRCLES_H__

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

SEXP DLL_EXPORT SDLfill_circles(SEXP graphicsVec, SEXP centerx, SEXP centery, SEXP radius, SEXP n);

#ifdef __cplusplus
}
#endif

#endif // __SDLFILL_CIRCLES_H__
