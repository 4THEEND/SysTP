#include "board.h"
#include "maingame.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    srand(time(NULL));
    board_t board;
    char gagnants[NB_JOUEURS]; // tableau de retour pour les gagnants
    for(int i = 0; i < NB_JOUEURS; i++){
        gagnants[i] = '0';
    }        
    init_board(&board);
    initialize_game(&board);
    play_game(&board, gagnants);
    printf("Les joueurs suivants ont remporté la partie: \n");
    for(int i = 0; i < NB_JOUEURS; i++){
        if(gagnants[i] != '0'){
            printf("- Le joueur %c \n", gagnants[i]);
        }
    }
    return 0;
}