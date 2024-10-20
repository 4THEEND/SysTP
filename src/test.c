#include "stack.h"
#include "g_interface.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>


void test_stack(void){
    stack_t s1 = {.m_pos = -1};
    assert(height(&s1) == 0);
    push(&s1, 'c');
    assert(top(&s1) == 'c');
    push(&s1, 'b');
    push(&s1, 'e');
    assert(peek(&s1, 2) == 'c');
    assert(peek(&s1, 1) == 'b');
    assert(pop(&s1) == 'e');
    assert(top(&s1) == 'b');
}

int main(){
    test_stack();

    srand(time(NULL));
    run_game();

    printf("Tous les test se sont bien déroulés :)\n");
    return 0;
}