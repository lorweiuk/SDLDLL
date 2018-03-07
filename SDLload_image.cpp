#include "SDLload_image.h"

SEXP DLL_EXPORT SDLload_image(SEXP imagein)
{
    // imagein to char*
    PROTECT( coerceVector(imagein, STRSXP) );
    const char* imagefile = CHAR( STRING_ELT(imagein, 0) );

    int dotpos     = 0;
    int stringsize = 0;
    while ( imagefile[stringsize] != '\0'  &&  stringsize < 1000 ) {
        // get size of string *imagefile and position of '.'
        if ( imagefile[stringsize] == '.' ) {
            dotpos = stringsize;
        }
        stringsize++;
    }

    if (stringsize >= 1000) {
        // no end-of-string char found in first 1000 chars of imagefile
        Rprintf("End of image filename-string ('\0') not found, check imagefile name of make name shorter.");
        return R_NilValue;
    }
    if (dotpos == 0) {
        // no dot char founf in filename
        Rprintf("No dot ('.') found in image filename, indicate file extension in image filename.");
        return R_NilValue;
    }

    // copy file extension
    char fext[stringsize - (dotpos-1)];
    int fextpos = 0;
    for (int pos = dotpos; pos <= stringsize; pos++) {
        fext[fextpos] = imagefile[pos];
        fextpos++;
    }

    // now load imageSurface depending on file ending and filename
    SDL_Surface* imageSurface;

    if (strcmp(fext, ".bmp") == 0) {
        imageSurface = SDL_LoadBMP(imagefile);
    }
    else if (strcmp(fext, ".jpeg") == 0) {
        int imageflag = IMG_INIT_JPG;
        if ( !(imageflag & IMG_Init(imageflag)) ) {
            Rprintf(IMG_GetError());
            return R_NilValue;
        }
        imageSurface = IMG_Load(imagefile);
    }
    else if (strcmp(fext, ".jpg") == 0) {
        int imageflag = IMG_INIT_JPG;
        if ( !(imageflag & IMG_Init(imageflag)) ) {
            Rprintf(IMG_GetError());
            return R_NilValue;
        }
        imageSurface = IMG_Load(imagefile);
    }
    else if (strcmp(fext, ".png") == 0) {
        int imageflag = IMG_INIT_PNG;
        if ( !(imageflag & IMG_Init(imageflag)) ) {
            Rprintf(IMG_GetError());
            return R_NilValue;
        }
        imageSurface = IMG_Load(imagefile);
    }
    else if (strcmp(fext, ".tif") == 0) {
        int imageflag = IMG_INIT_TIF;
        if ( !(imageflag & IMG_Init(imageflag)) ) {
            Rprintf(IMG_GetError());
            return R_NilValue;
        }
        imageSurface = IMG_Load(imagefile);
    }
    else {
        Rprintf("Imagefile extension did not match any of the allowed patterns: .bmp, .jpeg, .jpg, .png, .tif.");
        return R_NilValue;
    }

    // check whether loading image worked
    if (imageSurface == NULL) {
        Rprintf(SDL_GetError());
        return R_NilValue;
    }

    // make external pointer
    SEXP surfout;
    surfout = PROTECT( R_MakeExternalPtr(imageSurface, R_NilValue, R_NilValue) );
    R_RegisterCFinalizerEx(surfout, &SDLfinalizerSurface, TRUE);

    UNPROTECT(2);

    return surfout;
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
