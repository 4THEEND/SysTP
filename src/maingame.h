#ifndef MAINGAME_H
#define MAINGAME_H

#include "board.h"

int de();
void initialize_game(board_t* b);
bool allow_trapped_move(board_t* b, int ligne, int colonne);
bool peut_joueur_deplacer(board_t* b, char joueur);
bool peut_joueur_deplacer_ligne(board_t* b, int resulat_de);
char* get_winner(int* herissonFinis);
bool is_coordinate_valid(int ligne, int colonne);
bool is_ligne_vide(board_t* b, int ligne);
void play_game(board_t* b, char* gagnants);

#endif