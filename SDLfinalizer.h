
#ifndef __SDLFINALIZER_H__
#define __SDLFINALIZER_H__

#include <windows.h>
#include <R.h>
#include <Rinternals.h>
#include <SDL.h>
#include "SDL_mixer.h"
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

void SDLfinalizerWindow(SEXP extp);
void SDLfinalizerRenderer(SEXP extp);
void SDLfinalizerSurface(SEXP extp);
void SDLfinalizerEvent(SEXP extp);
void SDLfinalizerWav(SEXP extp);
void SDLfinalizerTexture(SEXP extp);
void SDLfinalizerFont(SEXP extp);

#ifdef __cplusplus
}
#endif

#endif // __SDLFILL_RECTS_H__
