#include "board.h"
#include <stdio.h>
#include <ctype.h>


void init_board(board_t* b){
    for (int i = 0; i < NB_LINE; i++){
        for (int j = 0; j < NB_ROW; j++){
            b->board_traps[i][j] = false;
            b->board[i][j].m_pos = -1;
        }
    }

    //TODO : put all special cells to true in board_traps
}


void board_push(board_t* b, int line, int row, char ctn){
    push(&b->board[line][row], ctn);
}

char board_pop(board_t* b, int line, int row){
    return pop(&b->board[line][row]);
}

int board_height(board_t* b, int line, int row){
    return height(&b->board[line][row]);
}

char board_top(board_t* b, int line, int row){
    return top(&b->board[line][row]);
}

char board_peek(board_t* b, int line, int row, int pos){
    return peek(&b->board[line][row], pos);
}

void cell_print_north(board_t* b, int line, int row, int slice){
    if (b->board_traps[line][row]){
        printf( "VVV ");
    }
    else{
        printf(" --- ");
    }
}

void cell_print_middle_north(board_t* b, int line, int row, int slice){
    char delimiter_l = ' ';
    char delimiter_r = ' ';
    if (b->board_traps[line][row]){
        delimiter_l = '>';
        delimiter_r = '<';
    }
    else{
        delimiter_l = '|';
        delimiter_r = '|';
    }

    // Use of left and right delimiters instead of producing redundant code of if else statements

    int height = board_height(b, line, row);
    if (height == 0){
        printf("%c   %c", delimiter_l, delimiter_r);
    }
    else{
        char fst_hedgehog = toupper(board_top(b, line, row));
        printf("%c%c%c%c%c",delimiter_l, fst_hedgehog, fst_hedgehog, fst_hedgehog, delimiter_r);
    }
}

void cell_print_middle_south(board_t* b, int line, int row, int slice){
    char delimiter_l = ' ';
    char delimiter_r = ' ';
    if (b->board_traps[line][row]){
        delimiter_l = '>';
        delimiter_r = '<';
    }
    else{
        delimiter_l = '|';
        delimiter_r = '|';
    }

    /*  Use of left and right delimiters instead of producing redundant code of if else statements
        We could've user 5 variables to pass arguments to printf but it'd have been less readable
    */

    int height = board_height(b, line, row);
    if (height == 0){
        printf("%c   %c", delimiter_l, delimiter_r);
    }
    else if(height == 1){
        char fst_hedgehog = toupper(board_top(b, line, row));
        printf("%c%c%c%c%c",delimiter_l, fst_hedgehog, fst_hedgehog, fst_hedgehog, delimiter_r);
    }
    else if(height == 2){
        char snd_hedgehog = board_peek(b, line, row, 1);
        printf("%c%c%c%c%c",delimiter_l, snd_hedgehog, snd_hedgehog, snd_hedgehog, delimiter_r);
    }
    else if(height == 3){
        char snd_hedgehog = board_peek(b, line, row, 1);
        char thd_hedgehog = board_peek(b, line, row, 2);
        printf("%c%c %c%c",delimiter_l, snd_hedgehog, thd_hedgehog, delimiter_r);
    } 
    else{
        char snd_hedgehog = board_peek(b, line, row, 1);
        char thd_hedgehog = board_peek(b, line, row, 2);
        char frt_hedgehog = board_peek(b, line, row, 3);
        printf("%c%c%c%c%c",delimiter_l, snd_hedgehog, thd_hedgehog, frt_hedgehog, delimiter_r);
    }
}

void cell_print_south(board_t* b, int line, int row, int slice){
    if (b->board_traps[line][row]){
        int height = board_height(b, line, row);
        if (height <= 1){
            printf(" ^^^ ");
        }
        else{
            printf(" ^%d^ ", height);
        }
    }
    else{
        int height = board_height(b, line, row);
        if (height <= 1){
            printf(" --- ");
        }
        else{
            printf(" -%d- ", height);
        }
    }
}

void cell_print(board_t* b, int line, int row, int slice){
    switch (slice){
        case 0:
            cell_print_north(b, line, row, slice);
            break;
        case 1:
            cell_print_middle_north(b, line, row, slice);
            break;
        case 2:
            cell_print_middle_south(b, line, row, slice);
            break;
        case 3:
            cell_print_south(b, line, row, slice);
            break;
    }
}

void board_print(board_t* b, int highlighted_line){
    printf("      START ");
    for(int i = 0; i < NB_ROW - 2; i++){
        printf("      ");
    }
    printf("FINISH\n\n");

    printf("     ");
    for(int i = 0; i < NB_ROW; i++){
        printf("  row  ");
    }
    printf("\n");

    printf("     ");
    for(int i = 0; i < NB_ROW; i++){
        printf("   %c   ", (char)((int)'a' + i));
    }
    printf("\n");

    for(int line = 0; line < NB_LINE; line++){
        for(int slice= 0; slice< 4; slice++){
            if(slice == 0){
                printf("      ");
            }
            else if(slice== 3){
                if(line == highlighted_line){
                    printf("    > ");
                }
                else{
                    printf("      ");
                }
            }
            else if(slice== 1){
                if(line == highlighted_line){
                    printf("line> ");
                }
                else{
                    printf("line  ");
                }
            }
            else{
                if(line == highlighted_line){
                    printf("  %d > ",line+1);
                }
                else{
                    printf("  %d   ",line+1);
                }
            }

            for(int row = 0; row < NB_ROW; row++){
                cell_print(b, line, row, slice);
                printf("  ");
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("     ");
    for(int i = 0; i < NB_ROW; i++){
        printf("  row  ");
    }
    printf("\n");

    printf("     ");
    for(int i = 0; i < NB_ROW; i++){
        printf("   %c   ", (char)((int)'a' + i));
    }
    printf("\n");
}