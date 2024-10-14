#ifndef STACK_H
#define STACK_H

#include "board.h"

typedef struct
{
    private:
        char m_stack[NB_JOUEURS_MAX];
        int m_pos_stack = 0;

    public:
        char pop();
        char top();
        int height();

} stack;

#endif

