#ifndef BOARD_H
#define BOARD_H

#include "stack.h"
#include <stdbool.h>

#define NB_LINE 3
#define NB_ROW 3
#define NB_TRAP 6
#define NB_JOUEURS 2
#define NB_HERISSONS 4

typedef struct{
    stack_t board[NB_LINE][NB_ROW];
    bool board_traps[NB_LINE][NB_ROW];
} board_t ;

void init_board(board_t* b);
void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos); // pos=0 => top
void cell_print(board_t* b, int line, int row, int slice);
void board_print(board_t* b, int highlighted_line); // hl_line=-1 => rien de s´electionner

// cell_print and board_print could also be used to debug the graphical interface in g_interface

#endif