#include "SDLopen.h"
#include "SDLfinalizer.h"

SEXP DLL_EXPORT SDLopen(SEXP x, SEXP y, SEXP w, SEXP h)
{
    // make SDL structures pointers
    SDL_Window*   window;
    SDL_Surface*  screenSurface;
    SDL_Renderer* myRenderer;
    SDL_Event*    myEvent = new SDL_Event();

    // coerce to right types (4 pr)
    PROTECT( x = coerceVector(x, INTSXP) );
    PROTECT( y = coerceVector(y, INTSXP) );
    PROTECT( w = coerceVector(w, INTSXP) );
    PROTECT( h = coerceVector(h, INTSXP) );

    // initialize, create window, get screen surface and renderer
    if (SDL_Init(SDL_INIT_VIDEO) < 0)   // SDL not initialized
    {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }
    else
    {
        if (INTEGER(x)[0]==0 && INTEGER(y)[0]==0 && INTEGER(w)[0]==0 && INTEGER(h)[0]==0) {
            window = SDL_CreateWindow("CREx", INTEGER(x)[0], INTEGER(y)[0], INTEGER(w)[0], INTEGER(h)[0], SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_INPUT_GRABBED );
        } else {
            window = SDL_CreateWindow("CREx", INTEGER(x)[0], INTEGER(y)[0], INTEGER(w)[0], INTEGER(h)[0], SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP );
        }
        if (window == NULL)   // no window initialized
        {
            Rprintf( SDL_GetError() );
            return R_NilValue;
        }
        else
        {
            screenSurface = SDL_GetWindowSurface( window ); // get window's surface
            myRenderer    = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            //if (SDL_SetHintWithPriority( SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE ) == SDL_TRUE ) {
            //    Rprintf("Vsync hint was set successfully.");
            //} else {
            //    Rprintf("Vsync hint could not be set.");
            //}
            SDL_RendererInfo ri;
            if (!SDL_GetRendererInfo(myRenderer, &ri)) {
                if (ri.name[0] != '\0' && ri.name[0]=='d' &&
                    ri.name[1] != '\0' && ri.name[1]=='i' &&
                    ri.name[2] != '\0' && ri.name[2]=='r' &&
                    ri.name[3] != '\0' && ri.name[3]=='e' &&
                    ri.name[4] != '\0' && ri.name[4]=='c' &&
                    ri.name[5] != '\0' && ri.name[5]=='t' &&
                    ri.name[6] != '\0' && ri.name[6]=='3' &&
                    ri.name[7] != '\0' && ri.name[7]=='d'&&
                    ri.name[8] == '\0') {
                        Rprintf("Direct3d9 renderer. Make sure to set Windows' OS flip queue size to 1 to get accurate timestamps for render_present().");
                } else if ( ri.name[0] != '\0' && ri.name[0]=='d' &&
                            ri.name[1] != '\0' && ri.name[1]=='i' &&
                            ri.name[2] != '\0' && ri.name[2]=='r' &&
                            ri.name[3] != '\0' && ri.name[3]=='e' &&
                            ri.name[4] != '\0' && ri.name[4]=='c' &&
                            ri.name[5] != '\0' && ri.name[5]=='t' &&
                            ri.name[6] != '\0' && ri.name[6]=='3' &&
                            ri.name[7] != '\0' && ri.name[7]=='d' &&
                            ri.name[8] != '\0' && ri.name[8]=='1' &&
                            ri.name[9] != '\0' && ri.name[9]=='1') {
                                Rprintf("Direct3d11 renderer.");
                } else {
                    Rprintf("No Direct3d9 or -11 renderer found. Present timestamps are not going to be accurate.");
                }
            }

            if (screenSurface == NULL  ||  myRenderer == NULL)
            {
                Rprintf( SDL_GetError() );
                return R_NilValue;
            }
        }
    }

    /*if (TTF_Init() == -1) {
        Rprintf( SDL_GetError() );
        return R_NilValue;
    }*/

    // set background to grey
    SDL_SetRenderDrawColor(myRenderer, 211, 211, 211, 255);
    SDL_RenderClear(myRenderer);

    // time the offset between GetTickCounter() and timeGetTime()
    SEXP ri        = PROTECT( allocVector(INTSXP, 1) );
    INTEGER(ri)[0] = 1;
    SEXP ro        = PROTECT( SDLset_timer_resolution(ri) );
    Sleep(200);

    int lastIncrement, lagSum;
    for (int i = 0; i < 100; ++i) {
        lastIncrement = GetTickCount();
        while (!(GetTickCount()-lastIncrement)) { ; }
        lagSum += GetTickCount() - timeGetTime();
    }
    lagSum             = (int)round((double)lagSum/100);
    SEXP lagOut        = PROTECT( allocVector(INTSXP, 1) );
    INTEGER(lagOut)[0] = lagSum;

    // empirically test refresh rate
    int diffsum = 0;
    int lastrefresh, newrefresh;
    for (int r = -10; r < 100; ++r) {
        SDL_RenderPresent(myRenderer, 0, 0);
        newrefresh = timeGetTime();
        if (r >= 0) {
            diffsum += newrefresh - lastrefresh;
        }
        lastrefresh = newrefresh;
    }
    double framesPerSec = diffsum / (double)100;
    SEXP framesOut      = PROTECT( allocVector(REALSXP, 1) );
    REAL(framesOut)[0]  = framesPerSec;

    // space and start value for last-nowait
    SEXP lastnowait        = PROTECT( allocVector(INTSXP, 1) );
    INTEGER(lastnowait)[0] = timeGetTime();

    // make graphics_list return-object (1 pr)
    SEXP graphicsVec;
    graphicsVec = PROTECT( allocVector(VECSXP, 11) );

    // also get font from SDLload_font()
    //SEXP fontp = PROTECT( SDLload_font( fontname, textsize ) );

    // make external pointers for SDL structures' pointers (4 Pr)
    SEXP extWindow        = PROTECT( R_MakeExternalPtr(window,        R_NilValue, R_NilValue) );
    SEXP extScreenSurface = PROTECT( R_MakeExternalPtr(screenSurface, R_NilValue, R_NilValue) );
    SEXP extRenderer      = PROTECT( R_MakeExternalPtr(myRenderer,    R_NilValue, R_NilValue) );
    SEXP extEvent         = PROTECT( R_MakeExternalPtr(myEvent,       R_NilValue, R_NilValue) );

    // register finalizer
    R_RegisterCFinalizerEx(extWindow,        &SDLfinalizerWindow,   TRUE);
    R_RegisterCFinalizerEx(extScreenSurface, &SDLfinalizerSurface,  TRUE);
    R_RegisterCFinalizerEx(extRenderer,      &SDLfinalizerRenderer, TRUE);
    R_RegisterCFinalizerEx(extEvent,         &SDLfinalizerEvent,    TRUE);

    int wout, hout;
    SDL_GetWindowSize(window, &wout, &hout); // output window dimensions

    // wout, hout to SEXP (2 Pr)
    SEXP swout, shout;
    swout = PROTECT( allocVector(INTSXP, 1));
    shout = PROTECT( allocVector(INTSXP, 1));
    INTEGER(swout)[0] = wout;
    INTEGER(shout)[0] = hout;

    // prepare output to graphics_list (6 Pr)
    PROTECT( SET_VECTOR_ELT(graphicsVec, 0, extWindow) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 1, extScreenSurface) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 2, extRenderer) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 3, extEvent) );
    //PROTECT( SET_VECTOR_ELT(graphicsVec, 4, fontp) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 4, swout) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 5, shout) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 6, ro) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 7, lagOut) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 8, framesOut) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 9, lastnowait) );
    PROTECT( SET_VECTOR_ELT(graphicsVec, 10, lastnowait) );

    UNPROTECT(27);

    return graphicsVec;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
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
}
