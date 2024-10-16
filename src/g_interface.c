#include "g_interface.h"
#include "board.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

void exit_sdl(){
    SDL_Quit();
}


void run_game(){
    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        fprintf(stderr, "[*] Failed to intialise SDL2: %s", SDL_GetError());
    }
    printf("[*] Sucessfully initialised SDL2\n");

    SDL_Window* window = SDL_CreateWindow("Igel Ärgern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL){
        fprintf(stderr, "[*] Failed to create the window with error: %s", SDL_GetError());
    }

    board_t board;
    init_board(&board);

    SDL_ShowWindow(window);
    SDL_Event event;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            printf("Touche haut enfoncée\n");
                            break;
                        case SDLK_DOWN:
                            printf("Touche bas enfoncée\n");
                            break;
                        case SDLK_SPACE:
                            printf("Touche espace enfoncée\n");
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }   

    SDL_DestroyWindow(window);
    printf("[*] Window exited sucessfully!!\n");
    exit_sdl();
}


void display_board(board_t* b){

}