
#ifndef __SDLAUDIO_RESUME_H__
#define __SDLAUDIO_RESUME_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_mixer.h"

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

SEXP DLL_EXPORT SDLaudio_resume();

#ifdef __cplusplus
}
#endif

#endif // __SDLAUDIO_RESUME_H__
