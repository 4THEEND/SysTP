#include "g_interface.h"
#include "board.h"
#include "maingame.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

void exit_sdl(int nb_free, SDL_Surface* to_free[]){
    for (int i = 0; i < nb_free; i++){
        if (to_free[i] != NULL)
            SDL_FreeSurface(to_free[i]);
    }
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
        exit_sdl(0, NULL);
    }

    SDL_ShowWindow(window);

    SDL_Surface* images_tab[NB_IMAGES] = {NULL, NULL, NULL, NULL, NULL};
    /*In images tab we have 
    0 : board image
    1 : red hedgehog image
    2 : blue hedgehog image
    3 : green hedgehog image
    4 : pink ? hedgehog image
    */

    images_tab[0] = SDL_LoadBMP(BOARD_BMP_PATH);
    if (images_tab[0] == NULL){
        fprintf(stderr, "[*] Failed to open the board image with error : %s\n", SDL_GetError());
        exit_sdl(0, NULL);
    }
    printf("[*] Sucessfully opened the board image\n");

    images_tab[1] = SDL_LoadBMP(RED_HG_BMP_PATH);
    if (images_tab[1] == NULL){
        fprintf(stderr, "[*] Failed to open the red hedgehog image with error : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, images_tab);
    }
    printf("[*] Sucessfully opened the red hedgehog image\n");

    images_tab[2] = SDL_LoadBMP(BLUE_HG_BMP_PATH);
    if (images_tab[2] == NULL){
        fprintf(stderr, "[*] Failed to open the blue hedgehog image with error : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, images_tab);
    }
    printf("[*] Sucessfully opened the blue hedgehog image\n");

    images_tab[3] = SDL_LoadBMP(GREEN_HG_BMP_PATH);
    if (images_tab[3] == NULL){
        fprintf(stderr, "[*] Failed to open the green hedgehog image with error : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, images_tab);
    }
    printf("[*] Sucessfully opened the green hedgehog image\n");

    SDL_Rect board_pos = {0, 0, 0, 0};
    if (SDL_BlitSurface(images_tab[0], NULL, SDL_GetWindowSurface(window), &board_pos) != 0){
        fprintf(stderr, "[*] Failed to bind the board image to the window : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, images_tab);
    }


    board_t board;
    init_board(&board);
    initialize_game(&board);
    int row = 0;
    int line = 0;

    display_board(&board, row, line); // first update before scanning for events
    SDL_UpdateWindowSurface(window); 

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
                            if (line > 0)
                                line--;
                            printf("Position : %d %d\n", row, line);
                            break;
                        case SDLK_DOWN:
                            if (line < NB_LINE - 1)
                                line++;
                            printf("Position : %d %d\n", row, line);
                            break;
                        case SDLK_LEFT:
                            if (row > 0)
                                row--;
                            printf("Position : %d %d\n", row, line);
                            break;
                        case SDLK_RIGHT:
                            if (row < NB_ROW - 1)
                                row++;
                            printf("Position : %d %d\n", row, line);
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
            display_board(&board, row, line);
            SDL_UpdateWindowSurface(window);
            
        }
    }   

    SDL_DestroyWindow(window);
    printf("[*] Window exited sucessfully!!\n");
    exit_sdl(NB_IMAGES, images_tab);
}


void display_board(board_t* b, int cursor_row, int cursol_line){

}


void DrawCircle(SDL_Renderer * renderer, int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}