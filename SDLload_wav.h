
#ifndef __SDLLOAD_WAV_H__
#define __SDLLOAD_WAV_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_mixer.h"
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

SEXP DLL_EXPORT SDLload_wav(SEXP wavfile);

#ifdef __cplusplus
}
#endif

#endif // __SDLLOAD_WAV_H__
