#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"

void move_piece(int piece_index);
void BeforeGame(void);
int roll_dice(void);
int Appear_mystery_cell(void);
void PlayerColour(int n);
int cointoss(void);
int Firstplayer(void);
void initialize_players(void);
int START(void);
int select_piece(int red_piece, int yellow_piece, int green_piece, int blue_piece, int value_useless);
int teleport_piece(int piece_index);
void check_capture(int piece_index);
void checking_for_blocks_in_the_path(int piece_index, int loc, int new_loc);
void move_block(void);
void teleport_block(void);
void move_piece(int piece_index);
int check_win(void);
void print_board(void);
void check_aura(int piece_index);
int red_AI(void);
int green_AI(void);
int yellow_AI(void);
int Blue_AI(int piece_index);
int block(int piece_index);
void break_block(void);
int going_in_to_HomeStraight(int piece_index);
#endif