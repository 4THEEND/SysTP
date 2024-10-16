#include "board.h"
#include "maingame.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    srand(time(NULL));
    board_t board;
    init_board(&board);
    initialize_game(&board);
    printf("Le grand gagnant est %d !!!", play_game(&board));
    return 0;
}