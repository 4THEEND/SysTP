#ifndef STACK_H
#define STACK_H

#define NB_JOUEURS_MAX 26

typedef struct{
    int m_pos;
    char m_tab_stack[NB_JOUEURS_MAX];
} stack_t;

void push(stack_t* pile, char elt);
char pop(stack_t* pile);
char peek(stack_t* pile, int pos);
char top(stack_t* pile);
int height(stack_t* pile);

// Initialise an array named NAME of (X*Y) stacks
#define init_stack_array(NAME, X, Y) stack_t NAME[X][Y]; for(int i = 0; i < X; i++){ for(int j = 0; j < Y; j++){ NAME[i][j].m_pos = -1; } }

#endif

