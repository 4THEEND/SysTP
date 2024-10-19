#ifndef G_INTERFACE_H
#define G_INTERFACE_H

#include <SDL2/SDL.h>
#include "board.h"

#define NB_IMAGES 9

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1032

#define HEDGEHOG_WIDTH 105
#define HEDGEHOG_HEIGHT 115

#define TOKEN_WIDTH 105
#define TOKEN_HEIGHT 75

#define NULL_PLAYER '0'

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
char getNextPlayer(char player);
char getNextPLayerVerified(char player, int nb_rows, board_t* b);
SDL_Texture* load_image(const char* path, SDL_Renderer* render, SDL_Window* window);
void exit_sdl(int nb_free, SDL_Texture* to_free[], SDL_Window* window, SDL_Renderer* render);
void clear_renderer(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* imgs[]);
bool move_hedgehog(board_t* b, int line_src, int row_src, int line_dest, int row_dest, char player);
void display_token(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int i, int j, SDL_Texture* imgs[], char player);
void display_hedgehog(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int i, int j, SDL_Texture* imgs[], int pos);
void display_board(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int cursor_row, int cursol_line, SDL_Texture* imgs[], char player);

#endif