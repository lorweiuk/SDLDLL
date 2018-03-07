#include "SDLtest.h"
#include "SDLset_render_color.h"
#include "SDLfill_circle.h"
#include "SDLdraw_rect.h"
#include "SDLrender_present.h"
#include "SDLdraw_circle.h"
#include "stdlib.h"
#include "time.h"

void DLL_EXPORT SDLtest(int* rendp, int* winp)
{
    int winw, winh;
    SDL_GetWindowSize((SDL_Window*)*winp, &winw, &winh);

    SDL_Color bgcolor = {0,0,0,255};
    SDL_SetRenderDrawColor((SDL_Renderer*)*rendp, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a );
    SDL_RenderClear((SDL_Renderer*)*rendp);

    SDL_Color circlecolor = {255,255,255,255};
    SDL_SetRenderDrawColor((SDL_Renderer*)*rendp, circlecolor.r, circlecolor.g, circlecolor.b, circlecolor.a);
    SDL_Point circlepositions[30];
    int radius = 6;
    char*
    for (int i = 0; i < 30; i++) {
        srand(i+1);
        circlepositions[i].x = rand() % winw;
        srand(i+1);
        circlepositions[i].y = rand() % winh;
        SDLfill_circle(rendp,&circlepositions[i].x,&circlepositions[i].y,&radius);
    }

    SDL_RenderPresent((SDL_Renderer*)*rendp);

}

/* extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
} */
