#include "board.h"


struct stack{
    char m_stack[NB_JOUEURS_MAX];
    int m_pos_stack;
};

void board_push(board_t* b, int line, int row, char ctn){
    
}

char board_pop(board_t* b, int line, int row){
    return 'a';
}

int board_height(board_t* b, int line, int row){
    return 0;
}

char board_top(board_t* b, int line, int row){
    return 'a';
}

char board_peek(board_t* b, int line, int row, int pos){
    return 'a';
}

void cell_print(board_t* b, int line, int row, int slice){
    
}

void board_print(board_t* b, int highlighted_line){
    
}