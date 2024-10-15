#include "board.h"
#include <stdlib.h>
#include <stdio.h>

int de(){
    return (rand() % NB_LINE)
}

int get_winner(int* herissonsFinis){ //retourne -1 s'il n'y a pas de gagnant
    for(int i = 0; i < NB_JOUEURS; i++){
        if(herissonsFinis[i] == (NB_HERISSONS - 1)){
            return i;
        }
    }
    return i;
}

bool is_coordinate_valid(int colonne, int ligne){
    bool is_colonne_valid = (colonne >= 1) && (colonne <= NB_COL);
    bool is_ligne_valid = (ligne >= 1 ) && (ligne <= NB_LINE);
    return is_colonne_valid && is_ligne_valid;
}

int play_game(board_t* b){ //retourne le joueur gagnant
    int herissonsFinis[NB_JOUEURS];
    for(int i = 0; i< NB_JOUEURS; i++){
        herissonsFinis[i] = 0;
    }
    int winner = -1:                                                    j
    while(winner = -1){
        for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
            int resultat_de = de();
            printf("Vous avez tiré un %d !\n", resultat_de);
            char veut_bouger;
            printf("Voulez-vous bouger un hérisson de ligne ? (Y/N): ");
            scanf("%c", &veut_bouger);
            while(veut_bouger != 'Y' && veut_bouger != 'N'){
                printf("Veuillez donner une réponse correcte, Y ou N: ");
                scanf("%c", &veut_bouger);
            }
            if(veut_bouger == 'Y'){
                int ligne_herisson;
                int col_herisson;
                int objectif;
                printf("Indiquez la ligne, puis la colonne du 
                herisson que vous souhaitez changer de ligne, ainsi que la ligne objectif. \n ");
                printf("Par exemple, pour déplacer le herisson dans la case (3,2) dans la ligne 4, on écrit 3 2 4. \n");
                scanf("%d %d %d", ligne_herisson, col_herisson, objectif);
            }
        }

    }


}