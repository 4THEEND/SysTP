#include <stdio.h>
#include "board.h"

int main(int argc, char** argv){
    board_t board;
    init_board(&board);
    board_print(&board, 2);
    return 0;
}