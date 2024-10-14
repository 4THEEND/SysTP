#ifndef STACK_H
#define STACK_H

#include "board.h"

typedef struct
{
    char m_stack[NB_JOUEURS_MAX];
    int m_pos_stack = 0;

    void push(char elt);
    char pop();
    char peek();
    char top();
    int height();

} stack;


#endif

