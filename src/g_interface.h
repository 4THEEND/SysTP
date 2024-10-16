#ifndef G_INTERFACE_H
#define G_INTERFACE_H

#include "board.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1032

#define BOARD_BMP_PATH "../images/board.bmp"



void run_game();
void display_board(board_t* b);

#endif