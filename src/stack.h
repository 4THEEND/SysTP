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

#endif

