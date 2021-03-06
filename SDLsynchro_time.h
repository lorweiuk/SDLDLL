#ifndef __SDLSYNCHRO_TIME_H__
#define __SDLSYNCHRO_TIME_H__

#include <windows.h>
#include <chrono>
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

SEXP DLL_EXPORT SDLsynchro_time();

#ifdef __cplusplus
}
#endif

#endif // __SDLSYNCHRO_TIME_H__
