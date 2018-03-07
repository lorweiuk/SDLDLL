#include "SDLpoll_event.h"

SEXP DLL_EXPORT SDLpoll_event(SEXP graphicsVec)
{
    // alloc output list
    SEXP output;
    output = PROTECT( allocVector(VECSXP, 5) );

    // get event pointer
    PROTECT( coerceVector(graphicsVec, VECSXP) );
    SDL_Event* eventp = (SDL_Event*) R_ExternalPtrAddr( VECTOR_ELT(graphicsVec, 3) );

    // output codes
    const char* type;
    int code = 0;
    int x    = 0;
    int y    = 0;
    int timestamp = 0;

    if (SDL_PollEvent(eventp) == 0) {
        type = NULL; // no event to report

    } else {
        switch (eventp->type) {

            case SDL_KEYDOWN: {
                type        = "key_down";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->key.keysym.sym;
                break;
            }
            case SDL_KEYUP: {
                type        = "key_up";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->key.keysym.sym;
                break;
            }


            case SDL_MOUSEBUTTONDOWN: {
                type        = "mouse_button_down";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->button.button;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                type        = "mouse_button_up";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->button.button;
                break;
            }
            case SDL_MOUSEMOTION: {
                type        = "mouse_motion";
                timestamp   = eventp->common.OStimestamp;
                x           = eventp->motion.x;
                y           = eventp->motion.y;
                break;
            }
            case SDL_MOUSEWHEEL: {
                type        = "mouse_wheel";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->wheel.direction;
                break;
            }


            case SDL_CONTROLLERAXISMOTION: {
                type        = "controller_axis_motion";
                timestamp   = eventp->common.timestamp;
                code        = eventp->caxis.axis;
                x           = eventp->caxis.value;
                break;
            }
            case SDL_CONTROLLERBUTTONDOWN: {
                type        = "controller_button_down";
                timestamp   = eventp->common.timestamp;
                code        = eventp->cbutton.button;
                break;
            }
            case SDL_CONTROLLERBUTTONUP: {
                type        = "controller_button_up";
                timestamp   = eventp->common.timestamp;
                code        = eventp->cbutton.button;
                break;
            }


            case SDL_JOYAXISMOTION: {
                type        = "joy_axis_motion";
                timestamp   = eventp->common.timestamp;
                code        = eventp->jaxis.axis;
                x           = eventp->jaxis.value;
                break;
            }
            case SDL_JOYBALLMOTION: {
                type        = "joy_ball_motion";
                timestamp   = eventp->common.timestamp;
                code        = eventp->jball.ball;
                x           = eventp->jball.xrel;
                y           = eventp->jball.yrel;
                break;
            }
            case SDL_JOYHATMOTION: {
                type        = "joy_hat_motion";
                timestamp   = eventp->common.timestamp;
                code        = eventp->jhat.hat;
                x           = eventp->jhat.value;
                break;
            }
            case SDL_JOYBUTTONDOWN: {
                type        = "joy_button_down";
                timestamp   = eventp->common.timestamp;
                code        = eventp->jbutton.button;
                break;
            }
            case SDL_JOYBUTTONUP: {
                type        = "joy_button_up";
                timestamp   = eventp->common.timestamp;
                code        = eventp->jbutton.button;
                break;
            }


            case SDL_WINDOWEVENT: {
                type        = "window_event";
                timestamp   = eventp->common.OStimestamp;
                code        = eventp->window.event;
                x           = eventp->window.data1;
                y           = eventp->window.data2;
                break;
            }


            case SDL_QUIT: {
                type        = "quit";
                timestamp   = eventp->common.timestamp;
                break;
            }
            default: {
                type = "unknown";
                break;
            }
        }
    }

    if (type == NULL) { // no event to report: return nil
        UNPROTECT(2);
        return R_NilValue;

    } else {
        // convert ints to SEXP
        SEXP stype      = PROTECT( allocVector(STRSXP, 1) );
        SEXP scode      = PROTECT( allocVector(INTSXP, 1) );
        SEXP sx         = PROTECT( allocVector(INTSXP, 1) );
        SEXP sy         = PROTECT( allocVector(INTSXP, 1) );
        SEXP stimestamp = PROTECT( allocVector(INTSXP, 1) );

        // assign
        SET_STRING_ELT(stype, 0, mkChar(type));
        INTEGER(scode)[0]      = code;
        INTEGER(sx)[0]         = x;
        INTEGER(sy)[0]         = y;
        INTEGER(stimestamp)[0] = timestamp;

        // fill in output list
        SET_VECTOR_ELT(output, 0, stype);
        SET_VECTOR_ELT(output, 1, scode);
        SET_VECTOR_ELT(output, 2, sx);
        SET_VECTOR_ELT(output, 3, sy);
        SET_VECTOR_ELT(output, 4, stimestamp);

        UNPROTECT(7);

        return output;
    }
}

/*extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
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
}*/
