

#ifndef __SDLCLOSE_H__
#define __SDLCLOSE_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDLfinalizer.h"
#include "SDLset_timer_resolution.h"
#include "SDL_ttf.h"

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

SEXP DLL_EXPORT SDLclose(SEXP graphicsVec);
SEXP DLL_EXPORT SDLclose_audio(SEXP wavp,   SEXP wavn);
SEXP DLL_EXPORT SDLclose_image(SEXP imagep, SEXP imagen);
SEXP DLL_EXPORT SDLclose_texture(SEXP texturep, SEXP texturen);
SEXP DLL_EXPORT SDLclose_font(SEXP fontp, SEXP fontn);

#ifdef __cplusplus
}
#endif

#endif // __SDLCLOSE_H__
