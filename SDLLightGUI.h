#ifdef __linux__ 
    #include <unistd.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_timer.h>
    #include <SDL2/SDL_ttf.h>
#elif _WIN32
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_timer.h>
    #include <SDL2/SDL_ttf.h>

    #define usleep _sleep
#elif _WIN64
    //#include <windows.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_timer.h>
    #include <SDL2/SDL_ttf.h>
    #define usleep _sleep
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>


#include "SDLwrapper.h"
#include "components/gui.h"
#include "components/window.h"
#include "components/gui.cpp"



