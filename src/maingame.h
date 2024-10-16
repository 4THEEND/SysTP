#ifndef MAINGAME_H
#define MAINGAME_H

#include "board.h"

int de();
int get_winner(int* herissonFinis);
bool is_coordinate_valid(int colonne, int ligne);
bool is_ligne_vide(board_t* b, int ligne);
int play_game(board_t* b);

#endif