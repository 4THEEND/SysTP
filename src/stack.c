#include "stack.h"
#include <assert.h>

void push(stack_t* pile, char elt){
    assert(pile->m_pos < NB_HEDGEHOG_MAX);
    pile->m_tab_stack[++pile->m_pos] = elt;
}

char pop(stack_t* pile){
    assert(pile->m_pos >= 0);
    return pile->m_tab_stack[pile->m_pos--];
}

char peek(stack_t* pile, int pos){
    assert(0 <= pos && pos <= pile->m_pos);
    return pile->m_tab_stack[pile->m_pos - pos];
}

char top(stack_t* pile){
    return peek(pile, 0);
}

int height(stack_t* pile){
    return pile->m_pos + 1;
}