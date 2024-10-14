#ifndef STACK_H
#define STACK_H

#include "board.h"

typedef struct stack stack_t;

void push(stack_t* pile, char elt);
char pop(stack_t* pile);
char peek(stack_t* pile, int pos);
char top(stack_t* pile);
int height(stack_t* pile);

#endif

