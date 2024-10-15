#include "board.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    srand(time(NULL));
    board_t board;
    init_board(&board);
    board_print(&board, 2);
    return 0;
}