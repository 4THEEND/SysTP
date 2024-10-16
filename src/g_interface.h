#ifndef G_INTERFACE_H
#define G_INTERFACE_H

#include "board.h"

#define NB_IMAGES 5

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1032

#define HEDGEHOG_WIDTH 105
#define HEDGEHOG_HEIGHT 115

#define BOARD_BMP_PATH "../images/board.bmp"
#define RED_HG_BMP_PATH "../images/red.bmp"
#define BLUE_HG_BMP_PATH "../images/blue.bmp"
#define GREEN_HG_BMP_PATH "../images/green.bmp"


SDL_Color burgundy_color = {129, 17, 17, 255};

void run_game();
void display_board(board_t* b, int cursor_row, int cursol_line);

#endif