#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


/************* 
This file implements the canonical version of the game as well as some auxiliary fonctions that will be useful elsewhere.
Will be used by executing ./igel
**************/


typedef struct{
    int first;
    int second;
} tuple;

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


//Prend en entrée un tableau indiquant, pour chaque joueur, le nombre de ses hérissons qui sont
//arrivés à la fin, et un tableau de taille NB_JOUEURS initialisé à '0' qui sera utilisé pour le retour.
// Retourne vrai s'il y a des gagnants, en indiquant lequels dans [gagnants], soit faux s'il y en a pas.
bool get_winner(int* herissonsFinis, char* gagnants){
    bool are_there_winners = false;
    int gagnants_position = 0;
    for(int i = 0; i < NB_JOUEURS; i++){
        if(herissonsFinis[i] == NB_HERISSONS - 1){
            gagnants[gagnants_position] = (char)((int)'a' + i);
            gagnants_position++;
            are_there_winners = true;
        }
    }
    return are_there_winners;
}

int comp_int_tuple(const void* a, const void* b){ // decreasing sort
    tuple t_a = *(const tuple*)a;
    tuple t_b = *(const tuple*)b;
    return t_b.first - t_a.first;
}

//Prend en entrée un tableau indiquant, pour chaque joueur, le nombre de ses hérissons qui sont
//arrivés à la fin, et un tableau de taille NB_JOUEURS initialisé à '0' qui sera utilisé pour le retour.
// Retourne vrai s'il y a des gagnants, en renvoyant le classement dans [gagnants],
// soit faux s'il y en pas
bool get_winner_right(int* herissonsFinis, char* gagnants){
    bool are_there_winners = false;
    tuple tab_tri[NB_JOUEURS];
    for(int i = 0; i < NB_JOUEURS; i++){
        if(herissonsFinis[i] == NB_HERISSONS - 1)
            are_there_winners = true;
        tab_tri[i].first = herissonsFinis[i];
        tab_tri[i].second = i;
    }

    qsort(tab_tri, NB_JOUEURS, sizeof(tuple), comp_int_tuple);

    for(int i = 0; i < NB_JOUEURS; i++){
        gagnants[i] = tab_tri[i].second + 'a';
    }
    return are_there_winners;
}

void clean_input_buffer(){
    char a;
    while ((a = getchar()) != '\n' && a != EOF) {

     }
}

bool is_coordinate_valid(int ligne, int colonne){
    bool is_colonne_valid = (colonne >= 0) && (colonne < NB_ROW);
    bool is_ligne_valid = (ligne >= 0 ) && (ligne < NB_LINE);
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

bool allow_trapped_move(board_t* b, int ligne, int colonne){
    for(int col = 0; col < colonne; col++){
        if(board_height(b, ligne, col) != 0){
            return false || !(b->board_traps[ligne][colonne]);
        }
    }
    return true;
}


bool peut_joueur_deplacer(board_t* b, char joueur){
    for(int ligne = 0; ligne < NB_LINE; ligne++){
        for(int col = 0; col < NB_ROW; col++){
            if((board_height(b, ligne, col) != 0) && (board_top(b, ligne, col) == joueur) && allow_trapped_move(b, ligne, col)){
                return true;
            }
        }
    }
    return false;
}

bool peut_joueur_deplacer_ligne(board_t* b, int resulat_de){
    for(int col = 0; col < NB_ROW - 1; col++){
        if((board_height(b, resulat_de, col) != 0) && allow_trapped_move(b, resulat_de, col)){
            return true;
        }
    }
    return false;
}


// Cette partie de la logique du jeu est utilisée tantôt ici comme pour la variante 22.
// Nous avons donc trouvé pertinent de la séparer afin de pouvoir la réutiliser dans les deux fichiers.
// Cette fonction demande au joueur les déplacements qu'il souhaite faire, en soignant que l'entrée de l'utilisateur
// soit correcte.
void tronc_commun(board_t* b, int joueur, int* herissonsFinis){
    int resultat_de = de();
    board_print(b, resultat_de);
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
        char col_herisson_tmp;
        int ligne_objectif;
        printf("Indiquez la ligne, puis la colonne du herisson que vous souhaitez changer de ligne, ainsi que la ligne ligne_objectif. \n ");
        printf("Par exemple, pour déplacer le herisson dans la case (3,b) dans la ligne 4, on écrit 3 b 4. \n");
        scanf("%d %c %d", &ligne_herisson, &col_herisson_tmp, &ligne_objectif);
        int col_herisson = (int)col_herisson_tmp + 1 - (int)'a';
        clean_input_buffer();
        while( !(is_coordinate_valid(ligne_herisson - 1, col_herisson - 1)) 
            || !(is_coordinate_valid(ligne_objectif - 1, 0)) 
            || (board_height(b, ligne_herisson - 1, col_herisson - 1) == 0) 
            || (board_top(b, ligne_herisson - 1, col_herisson - 1) != (char)(joueur + (int)'a'))
            || !(allow_trapped_move(b, ligne_herisson - 1, col_herisson - 1)) 
            || !(abs(ligne_herisson - ligne_objectif) <= 1)){
            printf("Veuillez à donner des coordonnées correctes, et choisir un de vos hérissons. \n");
            scanf("%d %c %d", &ligne_herisson, &col_herisson_tmp, &ligne_objectif);
            col_herisson = (int)col_herisson_tmp + 1 - (int)'a';
            clean_input_buffer();
        }
        board_pop(b, ligne_herisson - 1, col_herisson - 1);
        board_push(b, ligne_objectif - 1, col_herisson - 1, (char)((int)'a' + joueur));
    }
    if(is_ligne_vide(b, resultat_de)){
        printf("Vous ne pouvez bouger aucun hérisson, donc vous devez passer votre tour. \n");
    }
    else{
        char colonne_deplace_tmp;
        printf("Choisissez une colonne (une lettre): ");
        scanf("%c", &colonne_deplace_tmp);
        int colonne_deplace = (int)colonne_deplace_tmp + 1 - (int)'a';
        clean_input_buffer();
        while(!(is_coordinate_valid(0, colonne_deplace - 1)) || board_height(b, resultat_de, colonne_deplace - 1) == 0
        || !(allow_trapped_move(b, resultat_de, colonne_deplace - 1))){
            printf("Veuillez saisir une colonne valide non vide sans piège ou avec un piège désactivé: \n");
            scanf("%c", &colonne_deplace_tmp);
            colonne_deplace = (int)colonne_deplace_tmp + 1 - (int)'a';
            clean_input_buffer();
        }
        char player = board_pop(b, resultat_de, colonne_deplace - 1);
        board_push(b, resultat_de, colonne_deplace, player);
        if(colonne_deplace == NB_ROW - 1){
            herissonsFinis[(int)(player - (char)'a')]++;
            printf("Le herisson numéro %d du joueur %c est arrivé ! \n", herissonsFinis[(int)(player - (char)'a')], player);
        }
    }
}


void play_game(board_t* b, char* gagnants, int* herissonsFinis){ //retourne les joueurs gagnant                                     
    while(!(get_winner_right(herissonsFinis, gagnants))){
        for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
            printf("\n > C'est le tour au joueur %c !\n", (char)((int)'a' + joueur));
            tronc_commun(b, joueur, herissonsFinis); 
        }

    }
}