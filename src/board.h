#ifndef BOARD_H
#define BOARD_H

#define NB_ROW 3
#define NB_LINE 3
#define NB_JOUEURS_MAX 26

#include "stack.h"

typedef struct {
    stack* plateau[NB_LINE][NB_ROW];
} board_t;

void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos); // pos=0 => top
void cell_print(board_t* b, int line, int row, int slice);
void board_print(board_t* b, int highlighted_line); // hl_line=-1 => rien de s´electionner

#endif