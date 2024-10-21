#include "board.h"
#include "maingame.h"
#include "g_interface.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "doublescoring.h"

#define SHELL_KW "shell"
#define GRAPHICAL_KW "graphical"
#define VARIANT22_KW "variant"

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
        if (NB_LINE == 3 && NB_ROW == 9){
            run_game();
        }
        else{
            printf("Le nombre de ligne ou de colonne donné à la commilation n'est pas compatible avec l'interface grapique !! \n");
        }
    }
    else if(strcmp(argv[1], VARIANT22_KW) == 0){
        if(NB_JOUEURS != 2){
            printf("Désolé, cette variante se joue à deux joueurs. Veuillez changer NB_JOUEURS, défini dans board.h");
        }
        else{
            int objectif_points;
            printf("Saisissez le nombre de points nécessaires pour gagner: ");
            scanf("%d", &objectif_points);
            while(objectif_points <= 0){
                printf("Veuillez saisir un nombre de points strictement positif: ");
                scanf("%d", &objectif_points);
            }
            board_t board;
            init_board(&board);
            int winner = play_double_game(&board, objectif_points);
            if(winner == 2){
                printf("Match nul !");
            }
            else{
                printf("Le gagnant est le joueur %c !", (char)((int)'a' + winner));
            }
        }
    }
    else{
        printf("Argument invalide!!!\n");
    }
    return 0;
}