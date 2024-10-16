#ifndef MAINGAME_H
#define MAINGAME_H

#include "board.h"

int de();
void initialize_game(board_t* b);
bool peut_joueur_deplacer(board_t* b, char joueur);
int get_winner(int* herissonFinis);
bool is_coordinate_valid(int colonne, int ligne);
bool is_ligne_vide(board_t* b, int ligne);
int play_game(board_t* b);
bool allow_trapped_move(board_t* b, int ligne, int colonne);

#endif