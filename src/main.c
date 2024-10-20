#include "board.h"
#include "maingame.h"
#include "g_interface.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define SHELL_KW "shell"
#define GRAPHICAL_KW "graphical"

int main(int argc, char** argv){
    srand(time(NULL));

    if(argc < 2 || strcmp(argv[1], SHELL_KW) == 0){
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
    }
    else if(strcmp(argv[1], GRAPHICAL_KW) == 0){
        run_game();
    }
    else{
        printf("Argument invalide!!!\n");
    }
    return 0;
}