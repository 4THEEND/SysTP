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
        scoreJoueurs[loser] -= doubleFactor + 1;
        scoreJoueurs[winner] += doubleFactor + 1;
    }
    else if(herissonsFinis[0] == herissonsFinis[1] && herissonsFinis[0] == (NB_HERISSONS - 1)){
        scoreJoueurs[0] += (1 << doubleFactor);
        scoreJoueurs[1] += (1 << doubleFactor);
    }
    else{
        int winner;
        if (herissonsFinis[0] == NB_HERISSONS - 1){
            winner = 0;
        }
        else{
            winner = 1;
        }
        int loser = 1 - winner;
        scoreJoueurs[winner] += (1 << doubleFactor);
        scoreJoueurs[loser] -= herissonsFinis[loser]*(1 << doubleFactor);
    }
}

bool canDoubleGame(board_t* b){
    return is_ligne_vide(b, 0) && is_ligne_vide(b, 1);
}

void clear_board(board_t* b){
    for(int line = 0; line < NB_LINE; line++){
        for(int row = 0; row < NB_ROW; row++){
            while(board_height(b, line, row) != 0){
                board_pop(b, line, row);
            }
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
    int last_player_that_doubled;
    while(scoreJoueurs[0] < objectif_points && scoreJoueurs[1] < objectif_points){
        last_player_that_doubled = 2; //valeur arbitraire, l'important est qu'elle ne soit ni 0 ni 1
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
                printf("\n > C'est le tour au joueur %c !\n", (char)((int)'a' + joueur));
                if(canDoubleGame(b) && (joueur != last_player_that_doubled)){
                    char veut_doubler;
                    printf("Voulez-vous doubler la mise? La valeur actuelle du jeu est %d: (Y/N): ", (1 << doubleFactor));
                    scanf("%c", &veut_doubler);
                    clean_input_buffer();
                    while(veut_doubler != 'N' && veut_doubler != 'Y'){
                        printf("Veuillez donner une réponse valide, Y ou N: ");
                        scanf("%c", &veut_doubler);
                        clean_input_buffer();
                    }
                    if(veut_doubler == 'Y'){
                        printf("Le joueur %c veut doubler la valeur du jeu ! \n", (char)((int)'a' + joueur));
                        printf("Joueur %c, souhaitez-vous accepter la nouvelle mise ? (Y/N): ", (char)((int)'a' + (1-joueur)));
                        scanf("%c", &veut_doubler);
                        clean_input_buffer();
                        while(veut_doubler != 'N' && veut_doubler != 'Y'){
                          printf("Veuillez donner une réponse valide, Y ou N: ");
                          scanf("%c", &veut_doubler);
                          clean_input_buffer();
                        }
                        if(veut_doubler == 'Y'){
                            last_player_that_doubled = joueur;
                            doubleFactor++;
                            printf("La valeur du jeu est maintenant %d. \n", (1 << doubleFactor));
                            printf("\n > C'est toujours le tour au joueur %c !\n", (char)((int)'a' + joueur));
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
                else{
                    tronc_commun(b, joueur, herissonsFinis);
                }
            }
            is_there_winner = is_there_winner || get_winner(herissonsFinis, gagnants);    
        }
        updateScore(herissonsFinis, scoreJoueurs, doubleFactor, surrender);
        printf("Joueur a: %d points\n", scoreJoueurs[0]);
        printf("Joueur b: %d points\n", scoreJoueurs[1]);
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