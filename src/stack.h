#ifndef STACK_H
#define STACK_H

#include "board.h"

typedef struct
{
    char m_stack[NB_JOUEURS_MAX];
    int m_pos_stack = 0;

    void push(stack* pile, char elt);
    char pop(stack* pile);
    char peek(stack* pile);
    char top(stack* pile);
    int height(stack* pile);

} stack;


#endif

