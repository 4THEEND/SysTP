#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int de(){
    return (rand() % NB_LINE);
}

void initialize_game(board_t* b) {
    int ordre_joueurs[NB_JOUEURS];
    for(int i = 0; i < NB_JOUEURS; i++){
        ordre_joueurs[i] = i;
    }

    //permutation de Knuth
    int swap;
    int random_position;
    for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
        random_position = (rand() % (NB_JOUEURS - joueur)) + joueur;
        swap = ordre_joueurs[random_position];
        ordre_joueurs[random_position] = ordre_joueurs[joueur];
        ordre_joueurs[joueur] = swap;
    }
    
    for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
        for(int herisson = 0; herisson < NB_HERISSONS; herisson++){
            board_push(b, rand() % NB_LINE, 0, (char)((int)'a' + ordre_joueurs[joueur]));
        }
    }
}

int get_winner(int* herissonsFinis){ //retourne -1 s'il n'y a pas de gagnant
    for(int i = 0; i < NB_JOUEURS; i++){
        if(herissonsFinis[i] == (NB_HERISSONS - 1)){
            return i;
        }
    }
    return -1;
}

void clean_input_buffer(){
    char a;
    while ((a = getchar()) != '\n' && a != EOF) {

     }
}

bool is_coordinate_valid(int colonne, int ligne){
    bool is_colonne_valid = (colonne >= 1) && (colonne <= NB_ROW);
    bool is_ligne_valid = (ligne >= 1 ) && (ligne <= NB_LINE);
    return is_colonne_valid && is_ligne_valid;
}

bool is_ligne_vide(board_t* b, int ligne){
    bool is_empty = true;
    for(int i = 0; i < NB_ROW - 1; i++){
        if(board_height(b, ligne, i) != 0){
            is_empty = false;
        }
    }
    return is_empty;
}

bool peut_joueur_deplacer(board_t* b, char joueur){
    bool peut_il = false;
    for(int ligne = 0; ligne < NB_LINE; ligne++){
        for(int col = 0; col < NB_ROW; col++){
            if((board_height(b, ligne, col) != 0) && (board_top(b, ligne, col) == joueur)){
                peut_il = true;
            }
        }
    }
    return peut_il;
}

int play_game(board_t* b){ //retourne le joueur gagnant
    int herissonsFinis[NB_JOUEURS];
    for(int i = 0; i< NB_JOUEURS; i++){
        herissonsFinis[i] = 0;
    }
    int winner = -1;                                                
    while(winner == -1){
        for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
            int resultat_de = de();
            board_print(b, resultat_de);
            printf("C'est le tour au joueur %c !\n", (char)((int)'a' + joueur));
            printf("Vous avez tiré un %d !\n", resultat_de + 1);
            char veut_bouger;
            if(peut_joueur_deplacer(b, (char)((int)'a' + joueur))){
                printf("Voulez-vous bouger un hérisson de ligne ? (Y/N): ");
                scanf("%c", &veut_bouger);
                clean_input_buffer();
                while(veut_bouger != 'Y' && veut_bouger != 'N'){
                    printf("Veuillez donner une réponse correcte, Y ou N: ");
                    scanf("%c", &veut_bouger);
                   clean_input_buffer();
                }
            }
            else {
                printf("Vous ne pouvez changer de ligne aucun hérisson.\n");
                veut_bouger = 'N';
            }
            if(veut_bouger == 'Y'){
                int ligne_herisson;
                int col_herisson;
                int ligne_objectif;
                printf("Indiquez la ligne, puis la colonne du herisson que vous souhaitez changer de ligne, ainsi que la ligne ligne_objectif. \n ");
                printf("Par exemple, pour déplacer le herisson dans la case (3,2) dans la ligne 4, on écrit 3 2 4. \n");
                scanf("%d %d %d", &ligne_herisson, &col_herisson, &ligne_objectif);
                clean_input_buffer();
                while( !(is_coordinate_valid(ligne_herisson, col_herisson)) || !(is_coordinate_valid(ligne_objectif, 1)) 
                    || (board_height(b, ligne_herisson - 1, col_herisson - 1) == 0) || (board_top(b, ligne_herisson - 1, col_herisson - 1) != (char)(joueur + (int)'a')) ){
                    printf("Veuillez à donner des coordonnées correctes, et choisir un de vos hérissons. \n");
                    scanf("%d %d %d", &ligne_herisson, &col_herisson, &ligne_objectif);
                    clean_input_buffer();
                }
                board_pop(b, ligne_herisson - 1, col_herisson - 1);
                board_push(b, ligne_objectif - 1, col_herisson - 1, (char)((int)'a' + joueur));
            }
            if(is_ligne_vide(b, resultat_de)){
                printf("Vous ne pouvez bouger aucun hérisson, donc vous devez passer votre tour. \n");
            }
            else{
                int colonne_deplace;
                printf("Choisissez une colonne: ");
                scanf("%d", &colonne_deplace);
                clean_input_buffer();
                while(!(is_coordinate_valid(1, colonne_deplace)) || board_height(b, resultat_de, colonne_deplace - 1) == 0){
                    printf("Veuillez saisir une colonne valide non vide: \n");
                    scanf("%d", &colonne_deplace);
                    clean_input_buffer();
                }
                char player = board_pop(b, resultat_de, colonne_deplace - 1);
                board_push(b, resultat_de, colonne_deplace, player);
                if(colonne_deplace == NB_ROW){
                    herissonsFinis[(int)(player - (char)'a')]++;
                }
            }
        }

    }

    return 0;
}