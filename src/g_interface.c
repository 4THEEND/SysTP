#include "g_interface.h"
#include "board.h"
#include "maingame.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

void exit_sdl(int nb_free, SDL_Texture* to_free[], SDL_Window* window, SDL_Renderer* render){
    for (int i = 0; i < nb_free; i++){
        if (to_free[i] != NULL)
            SDL_DestroyTexture(to_free[i]);
    }
    if (render != NULL)
        SDL_DestroyRenderer(render);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

SDL_Texture* load_image(const char* path, SDL_Renderer* render, SDL_Window* window){
    SDL_Surface* image = SDL_LoadBMP(path);
    if (image == NULL){
        fprintf(stderr, "[*] Failed to open %s with error : %s\n", path, SDL_GetError());
        exit_sdl(0, NULL, window, render);
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(render, image);
    if (image_texture == NULL){
        fprintf(stderr, "[*] Failed to open %s with error : %s\n", path, SDL_GetError());
        exit_sdl(0, NULL, window, render);
    }
    SDL_FreeSurface(image);
    return image_texture;
}


void run_game(){
    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        fprintf(stderr, "[*] Failed to intialise SDL2: %s\n", SDL_GetError());
    }
    printf("[*] Sucessfully initialised SDL2\n");

    SDL_Window* window = SDL_CreateWindow("Igel Ärgern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL){
        fprintf(stderr, "[*] Failed to create the window with error: %s\n", SDL_GetError());
        exit_sdl(0, NULL, NULL, NULL);
    }
    printf("[*] Sucessfully created the window\n");
    SDL_ShowWindow(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        fprintf(stderr, "[*] Failed to create the renderer with error: %s\n", SDL_GetError());
        exit_sdl(0, NULL, window, NULL);
    }
    printf("[*] Sucessfully created the renderer\n");

    SDL_Texture* images_tab[NB_IMAGES] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    /*In images tab we have 
    0 : board image
    1 : red hedgehog image
    2 : blue hedgehog image
    3 : green hedgehog image
    4 : purple hedgehog image
    5 : purple token image
    6 : grenn token image
    7 : blue token image
    8 : red token image
    */

    images_tab[0] = load_image(BOARD_BMP_PATH, renderer, window); 
    images_tab[1] = load_image(RED_HG_BMP_PATH, renderer, window);
    images_tab[2] = load_image(BLUE_HG_BMP_PATH, renderer, window);
    images_tab[3] = load_image(GREEN_HG_BMP_PATH, renderer, window);
    images_tab[4] = load_image(PURPLE_HG_BMP_PATH, renderer, window);


    board_t board;
    init_board(&board);
    initialize_game(&board);
    int row = 0;
    int line = 0;

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
                            break;
                        case SDLK_DOWN:
                            if (line < NB_LINE - 1)
                                line++;
                            break;
                        case SDLK_LEFT:
                            if (row > 0)
                                row--;
                            break;
                        case SDLK_RIGHT:
                            if (row < NB_ROW - 1)
                                row++;
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
            display_board(&board, window, renderer,row, line, images_tab);
            SDL_UpdateWindowSurface(window);
            
        }
    }   

    SDL_DestroyWindow(window);
    printf("[*] Window exited sucessfully!!\n");
    exit_sdl(NB_IMAGES, images_tab, window, renderer);
}

void clear_renderer(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* imgs[]){
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0){
        fprintf(stderr, "[*] Failed to clear the renderer : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer); 
    }

    if (SDL_RenderClear(renderer)){
        fprintf(stderr, "[*] Failed to clear the renderer : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);   
    }
}

void display_board(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int cursor_row, int cursol_line, SDL_Texture* imgs[]){
    static const SDL_Color burgundy_color = {129, 17, 17, 255};

    clear_renderer(renderer, window, imgs);

    if (SDL_RenderCopy(renderer, imgs[0], NULL, NULL) != 0){
        fprintf(stderr, "[*] Failed to bind the board image to the window : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
    SDL_RenderPresent(renderer);
    if  (SDL_SetRenderDrawColor(renderer, burgundy_color.r, burgundy_color.g, burgundy_color.b, burgundy_color.a) != 0){
        fprintf(stderr, "[*] Failed to set the color : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
    DrawCircle(renderer, 100 + 150*cursor_row, 100 + 150*cursol_line, 50);
    SDL_RenderPresent(renderer);
}


void DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius)
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