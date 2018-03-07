
#ifndef __SDLENTRODUCE_H__
#define __SDLENTRODUCE_H__

#include <windows.h>
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

void DLL_EXPORT SDLentroduce();

#ifdef __cplusplus
}
#endif

#endif // __SDLENTRODUCE_H__
