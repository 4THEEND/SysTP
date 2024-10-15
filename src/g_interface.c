#include "g_interface.h"
#include <SDL2/SDL.h>
#include <stdbool.h>


void run_interface(){
    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        fprintf(stderr, "[*] Failed to intialise SDL2: %s", SDL_GetError());
    }
    printf("[*] Sucessfully initialised SDL2\n");

    SDL_Window* window = SDL_CreateWindow("Igel Ärgern", 0, 0 , WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL){
        fprintf(stderr, "[*] Failed to create the window with error: %s", SDL_GetError());
    }

    while(true){
        SDL_ShowWindow(window);
    }

    printf("[*] Window exited sucessfully!!\n");

    SDL_Quit();
}