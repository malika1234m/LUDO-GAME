#include "types.h"
#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int First_player;
int mystery_cell;

int rollvalue;
int toss;


int main(int argc, const char *argv[])
{

    srand(time(NULL));
    int n = 0, rounds = 0;
    int count_turns = 0;
    int count_mysteryturns = 0;
    BeforeGame();
    Firstplayer();
    initialize_players();
    while (1)
    {
        if (rounds >= 8)
        {
            int turns = (rounds - 8) % 16;
            if (turns == 0)
            {
                count_mysteryturns = 0;
            }

            if (count_mysteryturns == 0)
            {
                Appear_mystery_cell(); // appear a new mystery cell after 2 rounds

                count_mysteryturns++;
            }
        }
        START();
        int check_next_turn = rollvalue;

        if (check_next_turn == 6 && count_turns > 3)
        {
            // breaking the block the if it gets three 6s
            break_block();

            // Rule CS-6 : If any player has a blockade and rolls six consecutively three (3) times, in such cases,

            count_turns = 0;
            First_player = (First_player + 1) % TOTAL_PLAYERS;
            continue; // going to next player if player gets three 6s
        }
        int red_piece = -1;
        int yellow_piece = -1;
        int green_piece = -1;
        int blue_piece = -1;
        int moved_piece_in_previos_round; // for blue ai

        switch (First_player)
        {
        case 0:
        {   // choosing the best yellow piece to capture
            yellow_piece = yellow_AI();
        }
        break;
        case 1:
        {   // choosing the best blue piece to capture
            blue_piece = Blue_AI(moved_piece_in_previos_round);
        }
        break;
        case 2:
        {
            red_piece = red_AI();
            // choosing the best red piece to capture
        }
        break;
        case 3:
        {   // choosing the best green piece to capture
            green_piece = green_AI();
        }
        break;
        default:{}
        break;
        }
        int value_not_use = -1; // if we can't use piece index
        // needed when piece is in home straight
        int piece_index = select_piece(red_piece, yellow_piece, green_piece, blue_piece, value_not_use);
        if (piece_index == -1)
        {
            printf("no pieces to move\n");
        }
        if (players[First_player].pieces[piece_index].home_straight == 1)
        {
            int value = going_in_to_HomeStraight(piece_index);
            if (value == -1)
            {
                int value_useless = piece_index;
                piece_index = select_piece(red_piece, yellow_piece, green_piece, blue_piece, value_useless);
            }
        }
        // printf("\n selected piece         %d\n", piece_index);
        check_aura(piece_index);
        move_piece(piece_index);
        block(piece_index);
        // Pieces_go_startingPoint();
        print_board();
        moved_piece_in_previos_round = piece_index;

        if (check_win())
        {

            printf("\n");
            PlayerColour(First_player);
            printf(" player wins the game!\n");
            break; // End the game loop if there's a winner
        }
        printf("The mystery cell is at %d and will be at that location.\n", mystery_cell);
        if (check_next_turn != 6 || count_turns > 2)
        {
            players[First_player].block.block_capture = 0; 
            // resetting the block capture
            First_player = (First_player + 1) % TOTAL_PLAYERS; // going to next player
            count_turns = 0;
            rounds++;
            
            
        }
        if (check_next_turn == 6)
        {
            count_turns++;
            players[First_player].block.block_capture = 0; // resetting the block capture
        }
        printf("\nNumber of the Round = %d\n\n------------------------Next Player------------------------\n", rounds);
        n++;
    }
    return 0;
}