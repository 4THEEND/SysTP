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
        int herissonsFinis[NB_JOUEURS];
        for(int i = 0; i < NB_JOUEURS; i++){
            herissonsFinis[i] = 0;
        }   
        init_board(&board);
        initialize_game(&board);
        play_game(&board, gagnants, herissonsFinis);
        printf("Les classement final est: \n");
        int ranking = 1;
        int current_score = herissonsFinis[0];
        for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
            if(gagnants[joueur] != '0'){
                if(current_score != herissonsFinis[joueur]){
                    current_score = herissonsFinis[joueur];
                    ranking++;
                }
                printf("%d - Le joueur %c \n", ranking, gagnants[joueur]);
            }
        }
    }
    else if(strcmp(argv[1], GRAPHICAL_KW) == 0){
        if (NB_LINE == 6 && NB_ROW == 9 && NB_JOUEURS < 5){
            run_game();
        }
        else{
            printf("Le nombre de ligne, colonne ou de joueurs donné à la compilation n'est pas compatible avec l'interface graphique !! \n");
        }
    }
    else if(strcmp(argv[1], VARIANT22_KW) == 0){
        if(NB_JOUEURS != 2){
            printf("Désolé, cette variante se joue à deux joueurs. Veuillez changer NB_JOUEURS, défini dans board.h\n");
        }
        else{
            int objectif_points;
            printf("Saisissez le nombre de points nécessaires pour gagner: ");
            scanf("%d", &objectif_points);
            clean_input_buffer();
            while(objectif_points <= 0){
                printf("Veuillez saisir un nombre de points strictement positif: ");
                scanf("%d", &objectif_points);
                clean_input_buffer();
            }
            board_t board;
            init_board(&board);
            int winner = play_double_game(&board, objectif_points);
            if(winner == 2){
                printf("Match nul !\n");
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