#include "board.h"


struct board {
    stack_t plateau[NB_LINE][NB_ROW];
};

void board_push(board_t* b, int line, int row, char ctn){
    push(&b[line][row], ctn);
}

char board_pop(board_t* b, int line, int row){
    return pop(&b[line][row]);
}

int board_height(board_t* b, int line, int row){
    return height(&b[line][row]);
}

char board_top(board_t* b, int line, int row){
    return top(&b[line][row]);
}

char board_peek(board_t* b, int line, int row, int pos){
    return peek(&b[line][row], pos);
}

void cell_print(board_t* b, int line, int row, int slice){
    
}

void board_print(board_t* b, int highlighted_line){
    
}