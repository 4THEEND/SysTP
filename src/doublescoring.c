#include "board.h"
#include <stdio.h>
#include "maingame.h"
#include "doublescoring.h"

/* This version is a direct implementation of variant 22 as found in 
https://mquinson.frama.io/ensr-arcsys1/IgelArgernVariants.html. It must be played with
2 players.  */


// surrender vaut 0 si aucun joueur n'a refusé une offre de doublage, 1 si le joueur 'a' a
// refusé l'offre, 2 si le joueur 'b' a refusé l'offre.
void updateScore(int* herissonsFinis, int* scoreJoueurs, int doubleFactor, int surrender){
    if(surrender != 0){
        int loser = surrender - 1;
        int winner = 1 - loser;
        scoreJoueurs[loser] -= doubleFactor - 1;
        scoreJoueurs[winner] += doubleFactor + 1;
    }
    else if(herissonsFinis[0] == herissonsFinis[1] && herissonsFinis[0] == (NB_HERISSONS - 1)){
        scoreJoueurs[0] += (1 << doubleFactor);
        scoreJoueurs[1] += (1 << doubleFactor);
    }
    else{
        int winner = (herissonsFinis[0] == NB_HERISSONS - 1)?0:1;
        int loser = 1 - winner;
        scoreJoueurs[winner] += (1 << doubleFactor);
        scoreJoueurs[loser] -= herissonsFinis[loser]*(1 << doubleFactor);
    }
}

bool canDoubleGame(board_t* b){
    return is_ligne_vide(b, 0) && is_ligne_vide(b, 1);
}

void clear_board(board_t* b){
    char ignore;
    for(int line = 0; line < NB_LINE; line++){
        for(int row = 0; row < NB_ROW; row++){
            while(board_height(b, line, row) != 0){
                ignore = board_pop(b, line, row);
            }
        }
    }
}

void tronc_commun(board_t* b, int joueur, int* herissonsFinis){
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
        char col_herisson_tmp;
        int ligne_objectif;
        printf("Indiquez la ligne, puis la colonne du herisson que vous souhaitez changer de ligne, ainsi que la ligne ligne_objectif. \n ");
        printf("Par exemple, pour déplacer le herisson dans la case (3,b) dans la ligne 4, on écrit 3 b 4. \n");
        scanf("%d %c %d", &ligne_herisson, &col_herisson_tmp, &ligne_objectif);
        int col_herisson = (int)col_herisson_tmp + 1 - (int)'a';
        clean_input_buffer();
        while( !(is_coordinate_valid(ligne_herisson - 1, col_herisson - 1)) || !(is_coordinate_valid(ligne_objectif - 1, 0)) 
            || (board_height(b, ligne_herisson - 1, col_herisson - 1) == 0) 
            || (board_top(b, ligne_herisson - 1, col_herisson - 1) != (char)(joueur + (int)'a'))
            || !(allow_trapped_move(b, ligne_herisson - 1, col_herisson - 1)) ){
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
            printf("Un hérisson est arrivé ! \n");
        }
    }
}

// returns 0 if player 'a' won, 1 if player 'b' won, 2 if both won.

int play_double_game(board_t* b, int objectif_points){ 
    int scoreJoueurs[NB_JOUEURS];
    scoreJoueurs[0] = 0;
    scoreJoueurs[1] = 0;
    int herissonsFinis[NB_JOUEURS];
    char gagnants[NB_JOUEURS];
    int doubleFactor;
    bool is_there_winner;
    int surrender;
    while(scoreJoueurs[0] < objectif_points && scoreJoueurs[1] < objectif_points){
        doubleFactor = 0;
        surrender = 0;
        is_there_winner = false;
        for(int i = 0; i < NB_JOUEURS; i++){
            herissonsFinis[i] = 0;
        }
        clear_board(b);
        initialize_game(b);
        while(!is_there_winner){
            for(int joueur = 0; joueur < NB_JOUEURS; joueur++){
                if(canDoubleGame(b)){
                    char veut_doubler;
                    printf("Voulez-vous doubler la mise? La valeur actuelle du jeu est %d: (Y/N)", (1 << doubleFactor));
                    scanf("%c", &veut_doubler);
                    while(veut_doubler != 'N' && veut_doubler != 'Y'){
                        printf("Veuillez donner une réponse valide, Y ou N: ");
                        scanf("%c", &veut_doubler);
                    }
                    if(veut_doubler == 'Y'){
                        printf("Le joueur %c veut doubler la valeur du jeu ! \n", (char)((int)'a' + joueur));
                        printf("Joueur %c, souhaitez-vous accepter la nouvelle mise ? (Y/N)", (char)(int'a' + (1-joueur)));
                        scanf("%c", &veut_doubler);
                        while(veut_doubler != 'N' && veut_doubler != 'Y'){
                          printf("Veuillez donner une réponse valide, Y ou N: ");
                          scanf("%c", &veut_doubler);
                        }
                        if(veut_doubler == 'Y'){
                            doubleFactor++;
                            printf("La valeur du jeu est maintenant %d. \n", (1 << doubleFactor));
                            tronc_commun(b, joueur, herissonsFinis);
                        }
                        else{
                            surrender = 2 - joueur;
                            is_there_winner = true;
                        }
                    }
                    else{
                        tronc_commun(b, joueur, herissonsFinis);
                    }
                }
            }
            is_there_winner = is_there_winner || get_winner(herissonsFinis, gagnants);    
        }
        updateScore(herissonsFinis, scoreJoueurs, doubleFactor, surrender);
        printf("Joueur a: %d points", scoreJoueurs[0]);
        printf("Joueur b: %d points", scoreJoueurs[1]);
    }
    if(scoreJoueurs[0] == scoreJoueurs[1]){
        return 2;
    }
    else if(scoreJoueurs[0] >= objectif_points){
        return 0;
    }
    else{
        return 1;
    }
}