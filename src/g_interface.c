#include "g_interface.h"
#include "board.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

void exit_sdl(SDL_Surface* board_img){
    if (board_img != NULL)
        SDL_FreeSurface(board_img);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


void run_game(){
    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        fprintf(stderr, "[*] Failed to intialise SDL2: %s\n", SDL_GetError());
    }
    printf("[*] Sucessfully initialised SDL2\n");

    SDL_Window* window = SDL_CreateWindow("Igel Ärgern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL){
        fprintf(stderr, "[*] Failed to create the window with error: %s\n", SDL_GetError());
        exit_sdl(NULL);
    }

    SDL_ShowWindow(window);

    SDL_Surface* board_image = SDL_LoadBMP(BOARD_BMP_PATH);
    if (board_image == NULL){
        fprintf(stderr, "[*] Failed to open the board image with error : %s\n", SDL_GetError());
        exit_sdl(NULL);
    }
    printf("[*] Sucessfully opened the board image\n");

    SDL_Rect board_pos = {0, 0, 0, 0};
    if (SDL_BlitSurface(board_image, NULL, SDL_GetWindowSurface(window), &board_pos) != 0){
        fprintf(stderr, "[*] Failed to bind the board image to the window : %s\n", SDL_GetError());
        exit_sdl(NULL);
    }

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
            SDL_Delay(1000);
        }
        SDL_UpdateWindowSurface(window);
    }   

    board_t board;
    init_board(&board);

    SDL_DestroyWindow(window);
    printf("[*] Window exited sucessfully!!\n");
    exit_sdl(board_image);
}


void display_board(board_t* b){

}