#include "g_interface.h"
#include <SDL2/SDL.h>

void run_interface(){
    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        printf("[*] Failed initialisation of SDL2\n");
    }
    printf("[*] Initialisation of SDL2\n");

    SDL_Quit();
}