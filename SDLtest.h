#ifndef __SDLTEST_H__
#define __SDLTEST_H__

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

void DLL_EXPORT SDLtest(int* rendp, int* winp);

#ifdef __cplusplus
}
#endif

#endif // __SDLTEST_H__
