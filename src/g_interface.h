#ifndef G_INTERFACE_H
#define G_INTERFACE_H

#include <SDL2/SDL.h>
#include "board.h"

#define NB_IMAGES 9

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1032

#define HEDGEHOG_WIDTH 105
#define HEDGEHOG_HEIGHT 115

#define BOARD_BMP_PATH "../images/board.bmp"

#define RED_HG_BMP_PATH "../images/red.bmp"
#define BLUE_HG_BMP_PATH "../images/blue.bmp"
#define GREEN_HG_BMP_PATH "../images/green.bmp"
#define PURPLE_HG_BMP_PATH "../images/purple.bmp"

#define PURPLE_TOKEN_HG_BMP_PATH "../images/purple_token.bmp"
#define GREEN_TOKEN_HG_BMP_PATH "../images/green_token.bmp"
#define BLUE_TOKEN_HG_BMP_PATH "../images/blue_token.bmp"
#define RED_TOKEN_HG_BMP_PATH "../images/red_token.bmp"


void run_game();
SDL_Texture* load_image(const char* path, SDL_Renderer* render, SDL_Window* window);
void exit_sdl(int nb_free, SDL_Texture* to_free[], SDL_Window* window, SDL_Renderer* render);
void clear_renderer(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* imgs[]);
void display_board(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int cursor_row, int cursol_line, SDL_Texture* imgs[]);
void DrawCircle(SDL_Renderer * renderer, int centreX, int centreY, int radius); 
/* Mindpoint Circle Algorithm (found on stackoverflow) 
I'll try to implement it myself if I have enough time
*/

#endif