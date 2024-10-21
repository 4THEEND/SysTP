#ifndef STACK_H
#define STACK_H

#define NB_HEDGEHOG_MAX 100

typedef struct{
    int m_pos;
    char m_tab_stack[NB_HEDGEHOG_MAX];
} stack_t;

void push(stack_t* pile, char elt);
char pop(stack_t* pile);
char peek(stack_t* pile, int pos);
char top(stack_t* pile);
int height(stack_t* pile);

#endif

