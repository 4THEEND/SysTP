#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>


void test_stack(void){
    stack_t s1 = {.m_pos = -1};
    push(&s1, 'c');
    assert(top(&s1) == 'c');
}

int main(){
    test_stack();

    printf("Tous les test se sont bien déroulés :)\n");
    return 0;
}