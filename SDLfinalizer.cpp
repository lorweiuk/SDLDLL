#include "SDLfinalizer.h"

void SDLfinalizerWindow(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    SDL_Window* temp = (SDL_Window*) R_ExternalPtrAddr(extp);
    SDL_DestroyWindow(temp);
    R_ClearExternalPtr(extp);
}

void SDLfinalizerRenderer(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    SDL_Renderer* temp = (SDL_Renderer*) R_ExternalPtrAddr(extp);
    SDL_DestroyRenderer(temp);
    R_ClearExternalPtr(extp);
}

void SDLfinalizerSurface(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    SDL_Surface* temp = (SDL_Surface*) R_ExternalPtrAddr(extp);
    SDL_FreeSurface(temp);
    R_ClearExternalPtr(extp);
}

void SDLfinalizerEvent(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    SDL_Event* temp = (SDL_Event*) R_ExternalPtrAddr(extp);
    delete temp;
    R_ClearExternalPtr(extp);
}

void SDLfinalizerWav(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    Mix_Chunk* temp = (Mix_Chunk*) R_ExternalPtrAddr(extp);
    Mix_FreeChunk(temp);
    R_ClearExternalPtr(extp);
}

void SDLfinalizerTexture(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    SDL_Texture* temp = (SDL_Texture*) R_ExternalPtrAddr(extp);
    SDL_DestroyTexture(temp);
    R_ClearExternalPtr(extp);
}

void SDLfinalizerFont(SEXP extp)
{
    if (!R_ExternalPtrAddr(extp)) {
        return;
    }

    TTF_Font* temp = (TTF_Font*) R_ExternalPtrAddr(extp);
    TTF_CloseFont(temp);
    R_ClearExternalPtr(extp);
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
