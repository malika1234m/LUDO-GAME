#include "types.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int approach_points[] = {2, 15, 28, 41};

void move_piece(int piece_index);

void BeforeGame(void)
{
    printf("The red player has four (04) pieces named R1, R2, R3, and R4.\n");
    printf("The green player has four (04) pieces named G1, G2, G3, and G4.\n");
    printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4.\n");
    printf("The blue player has four (04) pieces named B1, B2, B3, and B4.\n\n\n");
}

int roll_dice(void)
{
    return (rand() % 6) + 1;
}
int Appear_mystery_cell(void)
{
    mystery_cell = rand() % 51;
    printf("\nA mystery cell has spawned in location %d and will be at this location for next four rounds\n", mystery_cell);
    return mystery_cell;
}
void PlayerColour(int n)
{
    n = n % 4;

    if (n == 0)
    {
        printf("Yellow");
    }
    else if (n == 1)
    {
        printf("Blue");
    }
    else if (n == 2)
    {
        printf("Red");
    }
    else if (n == 3)
    {
        printf("Green");
    }
}

int cointoss(void)
{
    toss = rand() % 2;
    if (toss == 0)
    {
        PlayerColour(First_player);
        printf("player gets tail. the piece would move in a anticlockwise direction");
    }
    else
    {
        PlayerColour(First_player);
        printf("player gets head. the piece would move in a clockwise direction");
    }
    return toss;
}
int Firstplayer(void)
{

    int drop[4];
    First_player = 0;
    for (int i = 0; i < 4; i++)
    {

        drop[i] = roll_dice();
        PlayerColour(i); // watch this

        printf("-->%d\n", drop[i]);
        if (drop[First_player] < drop[i])
        {
            First_player = i;
        }
    }
    PlayerColour(First_player);
    printf(" player has the highest roll and will begin the game\n");
    int name = First_player;
    printf("The order of a single round is ");
    PlayerColour(First_player);
    for (int j = 1; j < 4; j++)
    {
        name = First_player + j;
        if (j == 3)
        {
            printf(" and ");
        }
        else
        {
            printf(", ");
        }
        PlayerColour(name);
    }

    printf(".\n\n");
    return 0;
}
void initialize_players(void)
{
    const char *colors[] = {"Y", "B", "R", "G"};

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        players[i].color = colors[i];
        for (int j = 0; j < PIECES_for_PLAYER; j++)
        {
            players[i].pieces[j].position = -1;
            players[i].pieces[j].base = 0; // piece is in home
            players[i].pieces[j].approach = approach_points[i];
            players[i].pieces[j].capture = 0;
            players[i].pieces[j].round = 0;
            players[i].pieces[j].home_straight = 0;
            players[i].pieces[j].home_straight_position = 0;
            players[i].pieces[j].home_end = 0;
            players[i].pieces[j].block_active = 0;
            players[i].block.active = 0;
            players[i].block.size = 0;
            players[i].block.block_capture = 0;
            // players[i].block.block_homeactive=0;

            players[i].aura = 0;

            players[i].pieces[j].movement_speed = 1;
            players[i].turns = 0;
        }
    }
}

int START(void)
{
    int drop;
    drop = roll_dice();
    printf("\n");
    PlayerColour(First_player);
    printf("-->%d\n", drop);
    // First_player++;
    rollvalue = drop;
    printf("\n");

    return 0;
}

/*int Pieces_go_startingPoint(){

        if(rollvalue ==6){
            PlayerColour(First_player);
            printf(" goes to starting point\n");
            printf("\n");
            player1.piece1.base = 1;
        }
        else if(rollvalue !=6 && player1.piece1.base == 0){
            PlayerColour(First_player);
            printf(" stays in home\n");


        }else if(players1.piece[i].base == 0){
            players[i].piece[i].position += rollvalue;
            PlayerColour(First_player);
            printf(" goes to %d\n",players[i].piece[i].position);

        }


        return 0;
}*/

int select_piece(int red_piece, int yellow_piece, int green_piece, int blue_piece, int value_useless)
{

    if (red_piece != -1)
    { // this makes it first priority to capture the piece
        return red_piece;
    }
    if (yellow_piece != -1)
    {
        return yellow_piece;
    }
     if ( green_piece != -1)
    {
        return green_piece;
    }
     if (blue_piece != -1)
    {
        return blue_piece;
    }
    

    // First, check if there's an inactive piece and the dice rolled a 6
    if (rollvalue == 6)
    {
        for (int i = 0; i < PIECES_for_PLAYER; i++)
        {
            if (!players[First_player].pieces[i].base)
            {
                return i; // Return the index of the first inactive piece
            }
        }
    }
    int skip_piece_num;
    if (value_useless != -1)
    {
        skip_piece_num = value_useless;
    }

    // choose a random active piece
    int active_pieces[PIECES_for_PLAYER];
    int count = 0;
    for (int i = 0; i < PIECES_for_PLAYER; i++)
    {

        if (players[First_player].pieces[i].base && players[First_player].pieces[i].home_end == 0)
        {
            active_pieces[count] = i; // Collect indices of active pieces
            count++;
        }
    }

    if (count > 0)
    {
        return active_pieces[rand() % count]; // Return a random active piece
    }

    return -1; // If no  pieces  in board and dice didn't roll 6, return -1
}

int teleport_piece(int piece_index)
{

    // int Bhawana=1,
    int Bhawana_loc = 9;
    // int Kotuwa=2,
    int Kotuwa_loc = 27;
    //  int Pita_Kotuwa=3,
    int Pita_Kotuwa_loc = 46;
    // int Base=4;
    // int starting_point_of_the_piece=5;
    // int Approach_of_the_piece=6;

    int random_value = (rand() % 6) + 1;
    switch (random_value)
    {
    case 1:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to Bhawana\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = Bhawana_loc;
        players[First_player].pieces[piece_index].approach = Bhawana_loc;

        players[First_player].aura = (rand() % 2 + 1);

        if (players[First_player].aura == 1)
        {
            PlayerColour(First_player);
            printf(" piece %d feels energized, and movement speed doubles.\n", piece_index + 1);
            players[First_player].pieces[piece_index].movement_speed = 2;
        }
        else if (players[First_player].aura == 2)
        {
            PlayerColour(First_player);
            printf(" piece %d feels sick, and movement speed halves.\n", piece_index + 1);
            players[First_player].pieces[piece_index].movement_speed = (float)1 / 2;
            // ces ekk thinw
            // there is something wrong
        }
    }
    break;
    case 2:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to Kotuwa\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = Kotuwa_loc;
        players[First_player].pieces[piece_index].approach = Kotuwa_loc;
        PlayerColour(First_player);
        printf(" piece %d attends briefing and cannot move for four rounds.\n", piece_index + 1);
        players[First_player].aura = 3;
        players[First_player].pieces[piece_index].movement_speed = 0;
    }
    break;
    case 3:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to Pita_Kotuwa\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = Pita_Kotuwa_loc;
        players[First_player].pieces[piece_index].approach = Pita_Kotuwa_loc;
        if (players[First_player].pieces[piece_index].rotation == 0)
        {
            players[First_player].pieces[piece_index].rotation = 1; // goes to opposite side
        }
        else
        {
            players[First_player].pieces[piece_index].rotation = 0;
        }
    }
    break;
    case 4:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to Base\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = -1;
        players[First_player].pieces[piece_index].approach = approach_points[First_player];
        players[First_player].pieces[piece_index].base = 0;
    }
    break;
    case 5:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to starting point\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = 0;
        players[First_player].pieces[piece_index].approach = approach_points[First_player];
        players[First_player].pieces[piece_index].base = 1;
    }
    break;
    case 6:
    {
        PlayerColour(First_player);
        printf(" piece %d teleported to approach cell\n", piece_index + 1);
        players[First_player].pieces[piece_index].position = 52;
        players[First_player].pieces[piece_index].approach = approach_points[First_player] - 2; // going to home straight position
        players[First_player].pieces[piece_index].base = 1;
        if (players[First_player].pieces[piece_index].capture == 1)
        {
            PlayerColour(First_player);
            printf(" player's piece %d has reached the end!\n", piece_index + 1);

            players[First_player].pieces[piece_index].home_straight = 1;
        }
    }
    break;

    default:
        break;
    }

    return 0; // change this
}

// Function to check if a piece lands on an opponent's piece
void check_capture(int piece_index)
{
    if (players[First_player].pieces[piece_index].block_active == 0)
    {
        int new_position = players[First_player].pieces[piece_index].approach;

        for (int i = 0; i < TOTAL_PLAYERS; i++)
        {
            if (i == First_player)
                continue; // Skip the current player
        

            for (int j = 0; j < PIECES_for_PLAYER; j++)
            {
                if(players[i].pieces[j].block_active){
                    continue;
                    
                }
                // If another player's piece is at the same position, capture it
                if (players[i].pieces[j].approach == new_position && players[i].pieces[j].base && players[i].pieces[j].home_straight == 0)
                {
                    /*PlayerColour(i);
                    printf(" player's piece %d is captured by %s player's piece %d!\n", j + 1, players[First_player].color, piece_index + 1);*/

                    PlayerColour(First_player);
                    printf(" piece %d lands on square %d, captures ", piece_index + 1, new_position);
                    PlayerColour(i);
                    printf(" piece %d, and returns it to the base.\n", j + 1);
                    int number_inactive_pieces = 0;
                    for (int k = 0; k < PIECES_for_PLAYER; k++)
                    {
                        if (!players[First_player].pieces[k].base)
                        {
                            number_inactive_pieces++; // finding number of inactive pieces
                        }
                    }
                    PlayerColour(First_player);
                    printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base\n", (4 - number_inactive_pieces), number_inactive_pieces);

                    players[i].pieces[j].position = -1;
                    players[i].pieces[j].base = 0; // return the captured piece to base
                    players[i].pieces[j].approach = approach_points[i];
                    players[i].pieces[j].movement_speed = 1;
                    players[i].aura = 0;
                    players[First_player].pieces[piece_index].capture = 1;
                    // players[i].pieces[j].home_straight=0;//should change
                }
            }
        }
    }
    else
    { // block capture piece

        int new_position = players[First_player].pieces[piece_index].approach;

        for (int i = 0; i < TOTAL_PLAYERS; i++)
        {
            if (i == First_player)
                continue; // Skip the current player

            for (int j = 0; j < PIECES_for_PLAYER; j++)
            {
                // If another player's piece is at the same position, capture it
                if (players[i].pieces[j].approach == new_position && players[i].pieces[j].base && players[i].pieces[j].home_straight == 0)
                {
                    players[i].block.block_capture = 1;
                    int piece_in_home;
                    for (int q = 0; q < players[i].block.size; q++)
                    {
                        int piece_num = players[First_player].block.block_pieces[q];
                        if (players[First_player].pieces[piece_num].home_straight)
                        {

                            piece_in_home = piece_num;

                            // making sure to stop capturing the piece in home
                        }
                    }

                    if (players[First_player].block.size >= players[i].block.size)
                    {
                        // block captures another block
                        PlayerColour(First_player);
                        printf(" player's block of size %d lands on square %d captures ", players[First_player].block.size, new_position);
                        if (players[i].block.size != 0)
                        {
                            PlayerColour(i);
                            printf(" player's block of size %d and return all the pieces in block to base.\n\n", players[i].block.size);
                        }
                        else
                        {
                            // block capture a only one piece

                            PlayerColour(i);
                            printf(" player's piece and returns it to the base.%d\n\n", j + 1);
                            players[i].pieces[j].position = -1;
                            players[i].pieces[j].base = 0; // return the captured piece to base
                            players[i].pieces[j].approach = approach_points[i];
                            players[i].pieces[j].movement_speed = 1;
                            players[i].aura = 0;
                        }

                        int current_block_size = players[First_player].block.size;
                        for (int k = 0; k < current_block_size; k++)
                        {
                            int piece_num = players[First_player].block.block_pieces[k];
                            players[First_player].pieces[piece_num].capture = 1;
                        }

                        int captured_block_size = players[i].block.size;
                        for (int k = 0; k < captured_block_size; k++)
                        { // block size is more than 0
                            int piece_num = players[i].block.block_pieces[k];

                            if (piece_num == piece_in_home)
                            {
                                continue;
                            }

                            // players[i].pieces[piece_num].capture = 1;
                            players[i].pieces[piece_num].position = -1;
                            players[i].pieces[piece_num].base = 0; // return the captured piece to base
                            players[i].pieces[piece_num].approach = approach_points[i];
                            players[i].pieces[piece_num].movement_speed = 1;
                            players[i].pieces[piece_num].block_active = 0;
                            players[i].aura = 0;
                            players[i].block.active = 0;
                            players[i].block.size = 0;
                        }

                        int number_inactive_pieces = 0;
                        for (int k = 0; k < PIECES_for_PLAYER; k++)
                        {
                            if (!players[First_player].pieces[k].base)
                            {
                                number_inactive_pieces++; // finding number of inactive pieces
                            }
                        }
                        PlayerColour(First_player);
                        printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base\n", (4 - number_inactive_pieces), number_inactive_pieces);
                    }
                    else
                    {
                        // current block can't capture beacause it is smaller than other block
                        int current_block_size = players[First_player].block.size;
                        for (int k = 0; k < current_block_size; k++)
                        {
                            int piece_num = players[First_player].block.block_pieces[k];
                            players[First_player].pieces[piece_num].approach = players[i].pieces[j].approach - 1;
                            // making the block goes behind other block
                        }
                    }
                }
            }
        }
    }
}

void checking_for_blocks_in_the_path(int piece_index, int loc, int new_loc)
{
    if (players[First_player].pieces[piece_index].block_active)
    {
        // if block goes through

        int gone_to_new_location = 0;

        if (players[First_player].block.block_rotation)
        { // clockwise rotation
            for (int i = loc; i < new_loc; i++)
            {
                if (gone_to_new_location == 1)
                {
                    break;
                    // if it blocked by block break the loop because block can be blocked one time
                }
                for (int j = 0; j < TOTAL_PLAYERS; j++)
                {
                    if (j == First_player)
                    {
                        continue; // Skip the current player
                    }
                    if (gone_to_new_location == 1)
                    {
                        break;
                    }
                    for (int k = 0; k < TOTAL_PLAYERS; k++)
                    {
                        if (gone_to_new_location == 1)
                        {
                            break;
                        }
                        if (i == players[j].pieces[k].approach && players[j].pieces[k].block_active)
                        {
                            //        if(players[j].pieces[k].block_active){
                            if (players[j].block.size > players[First_player].block.size)
                            {

                                printf("\n");
                                PlayerColour(First_player);
                                printf(" player's block of size %d has been blocked by ", players[First_player].block.size);
                                PlayerColour(j);
                                printf(" player's block of size %d.\n", players[j].block.size);
                                for (int l = 0; l < TOTAL_PLAYERS; l++)
                                {
                                    if (players[First_player].pieces[l].block_active == 1)
                                    {

                                        players[First_player].pieces[l].approach = players[j].pieces[k].approach - 1;
                                        // stoping behind a block

                                        PlayerColour(First_player);
                                        printf(" Player piece %d in block of size %d moves to position %d in clockwise direction after been blocked by ", l + 1, players[First_player].block.size, players[First_player].pieces[l].approach);

                                        PlayerColour(j);
                                        printf(" player's block of size %d.\n", players[j].block.size);

                                        gone_to_new_location++;
                                    }
                                    else
                                    {
                                        continue;
                                    }
                                }
                                printf("\n");

                                /*  return 1;
                                 }else{
                                 //players[j].block.size<=players[First_player].block.size
                                 return 0;
                                 }

                                 }else{
                                 return 0;
                                 }
                                 */
                            }
                            //    }
                        }
                    }
                }
            }
        }
        else if (players[First_player].block.block_rotation == 0)
        {
            // anticlockwise rotation
            for (int i = loc; i > new_loc; i--)
            {
                if (gone_to_new_location == 1)
                {
                    break;
                }
                for (int j = 0; j < TOTAL_PLAYERS; j++)
                {
                    if (j == First_player)
                    {
                        continue; // Skip the current player
                    }
                    if (gone_to_new_location == 1)
                    {
                        break;
                    }
                    for (int k = 0; k < TOTAL_PLAYERS; k++)
                    {
                        if (gone_to_new_location == 1)
                        {
                            break;
                        }
                        if (i == players[j].pieces[k].approach && players[j].pieces[k].block_active)
                        {
                            //        if(players[j].pieces[k].block_active){
                            if (players[j].block.size > players[First_player].block.size)
                            {

                                printf("\n");
                                PlayerColour(First_player);
                                printf(" player's block of size %d has been blocked by ", players[First_player].block.size);
                                PlayerColour(j);
                                printf(" player's block of size %d.\n", players[j].block.size);
                                for (int l = 0; l < TOTAL_PLAYERS; l++)
                                {
                                    if (players[First_player].pieces[l].block_active == 1)
                                    {

                                        players[First_player].pieces[l].approach = players[j].pieces[k].approach - 1;
                                        // stoping behind a block

                                        PlayerColour(First_player);
                                        printf(" Player piece %d in block of size %d moves to position %d in anticlockwise direction after been blocked by ", l + 1, players[First_player].block.size, players[First_player].pieces[l].approach);

                                        PlayerColour(j);
                                        printf(" player's block of size %d.\n", players[j].block.size);

                                        gone_to_new_location++;
                                    }
                                    else
                                    {
                                        continue;
                                    }
                                }
                                printf("\n");

                                /*  return 1;
                                 }else{
                                 //players[j].block.size<=players[First_player].block.size
                                 return 0;
                                 }

                                 }else{
                                 return 0;
                                 }
                                 */
                            }
                            //    }
                        }
                    }
                }
            }
        }
    }
    else
    { // players[First_player].pieces[piece_index].block_active==0
        // if a piece goes

        int gone_to_new_location = 0;

        if (players[First_player].pieces[piece_index].rotation)
        {
            // clockwise rotation
            for (int i = loc; i < new_loc; i++)
            {
                if (gone_to_new_location == 1)
                {
                    break;
                }
                for (int j = 0; j < TOTAL_PLAYERS; j++)
                {
                    if (j == First_player)
                    {
                        continue; // Skip the current player
                    }
                    if (gone_to_new_location == 1)
                    {
                        break;
                    }
                    for (int k = 0; k < TOTAL_PLAYERS; k++)
                    {
                        if (i == players[j].pieces[k].approach && players[j].pieces[k].block_active)
                        {

                            if (gone_to_new_location == 1)
                            {
                                break;
                            }

                            PlayerColour(First_player);
                            printf(" player's piece %d has been blocked by ", piece_index + 1);
                            PlayerColour(j);
                            printf(" player's block of size %d.\n", players[j].block.size);

                            players[First_player].pieces[piece_index].approach = players[j].pieces[k].approach - 1;
                            // piece stopping behind a block

                            PlayerColour(First_player);
                            printf(" Player piece %d  moves to position %d in clockwise direction after been blocked by ", piece_index + 1, players[First_player].pieces[piece_index].approach);

                            PlayerColour(j);
                            printf(" player's block of size %d.\n", players[j].block.size);

                            gone_to_new_location++;

                            /*  return 1;
                             }else{
                             //players[j].block.size<=players[First_player].block.size
                             return 0;
                             }

                             }else{
                             return 0;
                             }
                             */
                        }
                    }
                }
            }
        }
        else
        {
            // anticlockwise rotation
            for (int i = loc; i > new_loc; i--)
            {
                if (gone_to_new_location == 1)
                {
                    break;
                }
                for (int j = 0; j < TOTAL_PLAYERS; j++)
                {
                    if (j == First_player)
                    {
                        continue; // Skip the current player
                    }
                    if (gone_to_new_location == 1)
                    {
                        break;
                    }
                    for (int k = 0; k < TOTAL_PLAYERS; k++)
                    {
                        if (i == players[j].pieces[k].approach && players[j].pieces[k].block_active)
                        {

                            if (gone_to_new_location == 1)
                            {
                                break;
                            }

                            PlayerColour(First_player);
                            printf(" player's piece %d has been blocked by ", piece_index + 1);
                            PlayerColour(j);
                            printf(" player's block of size %d.\n", players[j].block.size);

                            players[First_player].pieces[piece_index].approach = players[j].pieces[k].approach - 1;
                            // piece stopping behind a block

                            PlayerColour(First_player);
                            printf(" Player piece %d  moves to position %d in anticlockwise direction after been blocked by ", piece_index + 1, players[First_player].pieces[piece_index].approach);

                            PlayerColour(j);
                            printf(" player's block of size %d.\n", players[j].block.size);

                            gone_to_new_location++;

                            /*  return 1;
                             }else{
                             //players[j].block.size<=players[First_player].block.size
                             return 0;
                             }

                             }else{
                             return 0;
                             }
                             */
                        }
                    }
                }
            }
        }
    }
}

void move_block(int green_piece_num)
{
    //green_piece_num because green AI doesnot break block
    if (rollvalue >= players[First_player].block.size)
    { // block can move
        int movement = rollvalue / players[First_player].block.size;
        
        for (int i = 0; i < players[First_player].block.size; i++)
        {
            
            int piece_index = players[First_player].block.block_pieces[i];
            if (players[First_player].pieces[piece_index].base && players[First_player].pieces[piece_index].home_straight == 0)
            {
                if (players[First_player].block.block_rotation)
                { // Clockwise
                    players[First_player].pieces[piece_index].approach += movement * players[First_player].pieces[piece_index].movement_speed;
                    // players[First_player].pieces[piece_index].approach += movement;
                    if (players[First_player].pieces[piece_index].approach >= BOARD_SIZE)
                    {
                        players[First_player].pieces[piece_index].approach -= BOARD_SIZE;
                    }
                    // Print the new position for each piece in the block
                    PlayerColour(First_player);
                    printf("Player piece %d in block of size %d moves to position %d in clockwise direction\n", piece_index + 1, players[First_player].block.size, players[First_player].pieces[piece_index].approach);
                }
                else
                { // Anticlockwise
                    players[First_player].pieces[piece_index].approach -= movement * players[First_player].pieces[piece_index].movement_speed;
                    // players[First_player].pieces[piece_index].approach -= movement;
                    if (players[First_player].pieces[piece_index].approach < 0)
                    {
                        players[First_player].pieces[piece_index].approach += BOARD_SIZE;
                    }
                    
                    // Print the new position for each piece in the block
                    PlayerColour(First_player);
                    printf("Player piece %d in block of size %d moves to position %d in anticlockwise direction\n", piece_index + 1, players[First_player].block.size, players[First_player].pieces[piece_index].approach);
                }
            }
        }
        // do here
        
        int j = 0;
        int piece_index = players[First_player].block.block_pieces[j];
        int loc, new_loc;
        if (players[First_player].block.block_rotation)
        { // Clockwise
            new_loc = players[First_player].pieces[piece_index].approach;
            loc = players[First_player].pieces[piece_index].approach - movement * players[First_player].pieces[piece_index].movement_speed;
        }
        else
        {
            // Anticlockwise
            new_loc = players[First_player].pieces[piece_index].approach;
            loc = players[First_player].pieces[piece_index].approach + movement * players[First_player].pieces[piece_index].movement_speed;
        }
        
        checking_for_blocks_in_the_path(piece_index, loc, new_loc); // checking if there are blocks in the path
    }
    else
    {
        // breaking the block to move one piece because roll value is smaller
        
        if(First_player==3){//green Ai doesnot intend to break the block
            int next_green_piece_index=green_piece_num;
            while(players[First_player].pieces[next_green_piece_index].block_active == 0){
                next_green_piece_index= (green_piece_num+1)%TOTAL_PLAYERS;//go to next piece
                move_piece(next_green_piece_index);
                if(players[First_player].block.size==4){
                    printf("Green player has a block size of 4.Therefore no Green piece will move\n");
                    break;
                }
                
            }
        }else
        {
        
        int size = players[First_player].block.size;
        int suggest_piece = rand() % size;
        
        int piece_num = players[First_player].block.block_pieces[suggest_piece]; // selecting a random piece from the block to move
        
        if (players[First_player].pieces[piece_num].base && players[First_player].pieces[piece_num].home_straight == 0)
        {
            if (players[First_player].pieces[piece_num].rotation)
            { // clockwise rotation
                
                players[First_player].pieces[piece_num].position += (rollvalue * players[First_player].pieces[piece_num].movement_speed); // Move the piece forward
                int loc = players[First_player].pieces[piece_num].approach;
                players[First_player].pieces[piece_num].approach += (rollvalue * players[First_player].pieces[piece_num].movement_speed);
                
                if (players[First_player].pieces[piece_num].approach > 51)
                { // keeping approach between 1-52
                    players[First_player].pieces[piece_num].approach -= BOARD_SIZE;
                }
                int new_loc = players[First_player].pieces[piece_num].approach;
                PlayerColour(First_player);
                printf(" moves piece %d from location %d to %d by %d units in clockwise direction\n", piece_num + 1, loc, new_loc, new_loc - loc);
                // PlayerColour(First_player);
                //printf(" piece %d goes to %d\n", piece_num + 1, players[First_player].pieces[piece_num].approach);
            }
            else
            {
                players[First_player].pieces[piece_num].position -= (rollvalue * players[First_player].pieces[piece_num].movement_speed); // Move the piece backward
                
                int loc = players[First_player].pieces[piece_num].approach; // storing first loc of piece
                
                players[First_player].pieces[piece_num].approach -= (rollvalue * players[First_player].pieces[piece_num].movement_speed);
                
                int new_loc = players[First_player].pieces[piece_num].approach;
                
                if (players[First_player].pieces[piece_num].approach < 0)
                {
                    players[First_player].pieces[piece_num].approach += BOARD_SIZE;
                }
                
                PlayerColour(First_player);
                printf(" moves piece %d from location %d to %d by %d units in anticlockwise direction.\n", piece_num + 1, loc, new_loc, (loc - new_loc));
                //  PlayerColour(First_player);
                //printf(" piece %d goes to %d\n", piece_num + 1, players[First_player].pieces[piece_num].approach);
            }
        }
        if (players[First_player].pieces[piece_num].approach == mystery_cell)
        {
            teleport_piece(piece_num);
        }
        
        if (players[First_player].pieces[piece_num].capture == 1 && players[First_player].pieces[piece_num].approach == (approach_points[First_player] - 2))
        {
            // players[First_player].pieces[piece_index].position = BOARD_SIZE;  // going to home
            PlayerColour(First_player);
            printf(" player's piece %d has reached the end!\n", piece_num + 1);
            
            players[First_player].pieces[piece_num].home_straight = 1;
        }
        for (int r = 0; r < size; r++)
        {
            int piece = players[First_player].block.block_pieces[r];
            
            players[First_player].pieces[piece].block_active = 0; // block breaks
            
            players[First_player].block.size = 0;
            players[First_player].block.active = 0;
            players[First_player].block.block_capture = 0;
            if (piece_num != piece)
            {
                rollvalue = (rand() % 5) + 1;
                
                move_piece(piece);
            }
            else
            {
                continue; // we cant put dice again for moved piece by breaking the block
            }
        }
        PlayerColour(First_player);
        printf("'s block of size %d breaks\n", size);
    }}

    int size = players[First_player].block.size;
    for (int i = 0; i < size; i++)
    {
        int piece_num = players[First_player].block.block_pieces[i];
        if (players[First_player].pieces[piece_num].approach == mystery_cell)
        {

            players[First_player].pieces[piece_num].block_active = 0; // after teleport block breaks

            players[First_player].block.size = 0;
            players[First_player].block.active = 0;
            players[First_player].block.block_capture = 0;

            teleport_piece(piece_num);
        }
    }

    for (int i = 0; i < size; i++)
    {
        int piece_num = players[First_player].block.block_pieces[i];
        if (players[First_player].pieces[piece_num].capture == 1 && players[First_player].pieces[piece_num].approach == (approach_points[First_player] - 2))
        {
            // players[First_player].pieces[piece_index].position = BOARD_SIZE;  // going to home
            PlayerColour(First_player);
            printf(" player's piece %d has reached the end!\n", piece_num + 1);

            players[First_player].pieces[piece_num].home_straight = 1;

            // if only one piece is going to home straight block should reduce one piece
            players[First_player].pieces[piece_num].block_active = 0;
            // i have to change this
            // players[First_player].block.size--;
            for (int r = 0; r < size; r++)
            {
                int piece = players[First_player].block.block_pieces[r];

                players[First_player].pieces[piece].block_active = 0; // block breaks

                players[First_player].block.size = 0;
                players[First_player].block.active = 0;
                players[First_player].block.block_capture = 0;

                rollvalue = (rand() % 5) + 1;

                move_piece(piece); // moving other pieces which doesnot goes to home
            }
            PlayerColour(First_player);
            printf("'s block of size %d breaks\n", size);
        }
        else
        {
            if (players[i].block.block_capture == 0)
            {
                check_capture(piece_num);
            }
        }
    }
}
void teleport_block(void)
{

    for (int i = 0; i < players[First_player].block.size; i++)
    {
        teleport_piece(i);
        players[First_player].pieces[i].block_active = 0; // after tele

        players[First_player].block.active = 0;
    }
}
// Function to move a piece for a player
void move_piece(int piece_index)
{

    if (piece_index == -1)
        return; // No valid piece to move

    if (players[First_player].pieces[piece_index].base && players[First_player].pieces[piece_index].home_straight == 0)
    {
        if (players[First_player].pieces[piece_index].block_active == 0) //|| players[First_player].block.active==0)
        {
            if (players[First_player].pieces[piece_index].rotation)
            { // clockwise rotation

                players[First_player].pieces[piece_index].position += (rollvalue * players[First_player].pieces[piece_index].movement_speed); // Move the piece forward
                int loc = players[First_player].pieces[piece_index].approach;
                players[First_player].pieces[piece_index].approach += (rollvalue * players[First_player].pieces[piece_index].movement_speed);

                if (players[First_player].pieces[piece_index].approach > 51)
                { // keeping approach between 1-52
                    players[First_player].pieces[piece_index].approach -= BOARD_SIZE;
                }
                int new_loc = players[First_player].pieces[piece_index].approach;

                int diffrence_of_locations = new_loc - loc;
                if (diffrence_of_locations < 0)
                {
                    diffrence_of_locations += 52;
                }
                PlayerColour(First_player);
                printf(" moves piece %d from location %d to %d by %d units in clockwise direction\n", piece_index + 1, loc, new_loc, diffrence_of_locations);
                // PlayerColour(First_player);
                // printf(" piece %d goes to %d\n", piece_index + 1, players[First_player].pieces[piece_index].approach);
                checking_for_blocks_in_the_path(piece_index, loc, new_loc); // checking if there are blocks in the path
            }
            else
            {
                players[First_player].pieces[piece_index].position -= (rollvalue * players[First_player].pieces[piece_index].movement_speed); // Move the piece backward

                int loc = players[First_player].pieces[piece_index].approach; // storing first loc of piece

                players[First_player].pieces[piece_index].approach -= (rollvalue * players[First_player].pieces[piece_index].movement_speed);

                if (players[First_player].pieces[piece_index].approach < 0)
                {
                    players[First_player].pieces[piece_index].approach += BOARD_SIZE;
                }
                int new_loc = players[First_player].pieces[piece_index].approach;
                int diffrence_of_locations = (loc - new_loc);
                if (diffrence_of_locations < 0)
                {
                    diffrence_of_locations += 52;
                }

                PlayerColour(First_player);
                printf(" moves piece %d from location %d to %d by %d units in anticlockwise direction.\n", piece_index + 1, loc, new_loc, diffrence_of_locations);
                // PlayerColour(First_player);
                // printf(" piece %d goes to %d\n", piece_index + 1, players[First_player].pieces[piece_index].approach);
                checking_for_blocks_in_the_path(piece_index, loc, new_loc); // checking if there are blocks in the path
            }

            if (players[First_player].pieces[piece_index].approach == mystery_cell)
            {
                teleport_piece(piece_index);
            }

            if (players[First_player].pieces[piece_index].capture == 1 && players[First_player].pieces[piece_index].approach == (approach_points[First_player] - 2))
            {
                // players[First_player].pieces[piece_index].position = BOARD_SIZE;  // going to home
                PlayerColour(First_player);
                printf(" player's piece %d has reached the end!\n", piece_index + 1);

                players[First_player].pieces[piece_index].home_straight = 1;
            }
            else
            {
                check_capture(piece_index);
            }
        }
        else
        {
            move_block(piece_index);
        }
    }
    else if (rollvalue == 6)
    {
        players[First_player].pieces[piece_index].base = 1;     // Activate the piece
        players[First_player].pieces[piece_index].position = 0; // Place the piece at the starting position
        PlayerColour(First_player);
        printf(" player's piece %d goes to the starting point!\n", piece_index + 1);
        int number_inactive_pieces = 0;
        for (int i = 0; i < PIECES_for_PLAYER; i++)
        {
            if (!players[First_player].pieces[i].base)
            {
                number_inactive_pieces++; // finding number of inactive pieces
            }
        }
        PlayerColour(First_player);
        printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base\n", (4 - number_inactive_pieces), number_inactive_pieces);
        cointoss();
        players[First_player].pieces[piece_index].rotation = toss;
    }
}

int check_win(void)
{
    for (int i = 0; i < PIECES_for_PLAYER; i++)
    {
        if (players[First_player].pieces[i].home_end == 0)
        {
            return 0; // Return 0 if any piece hasn't reached the appproach point after capturing
        }
    }
    return 1;
}

void print_board(void)
{
    printf("\nSummary\n\n");

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        int summaryplayer = First_player + i;
        if (summaryplayer > 3)
        {
            summaryplayer = summaryplayer % 4;
        }
        printf("===========================================================\n");
        printf(" Location of pieces ");
        PlayerColour(summaryplayer);
        printf(" \n");
        printf("===========================================================\n");

        for (int j = 0; j < PIECES_for_PLAYER; j++)
        {
            printf("Piece %d ---->  %d", j + 1, players[summaryplayer].pieces[j].approach);
            if (!players[summaryplayer].pieces[j].base)
            {
                printf("\t  BASE");
            }
            if (players[summaryplayer].pieces[j].home_straight)
            {
                printf("\t  HOME -> %d  ",players[summaryplayer].pieces[j].home_straight_position);
            }
            if (players[summaryplayer].pieces[j].home_end)
            {
                printf("\t\tFinally HOME");
            }
            if (players[summaryplayer].pieces[j].block_active)
            {
                printf(" Block");
            }

            printf("\n");
        }
        printf("\n");
    }
    printf("\n\n");
    /*for (int i = 0; i < TOTAL_PLAYERS; i++) {
        int summaryplayer= First_player+i;
        if(summaryplayer>3){
            summaryplayer= summaryplayer%4;
        }
        PlayerColour(summaryplayer);
        printf(" player win positions: ");

        for (int j = 0; j < PIECES_for_PLAYER; j++) {
            printf("%d ", players[summaryplayer].pieces[j].position);
        }
        printf("\n");
    }*/
}
void check_aura(int piece_index)
{
    // counting turns in auraaaaaaaaa
    if (!(players[First_player].aura == 0))
    {
        players[First_player].turns++;
    }
    if (!(players[First_player].aura == 0) && (players[First_player].turns == 4))
    {                                                                 //(rounds%16==0)meka weradi bnnnnnnnnnnnn
        players[First_player].pieces[piece_index].movement_speed = 1; // making the speed ==1
        players[First_player].turns = 0;
        players[First_player].aura = 0;
    }
}

int red_AI(void)
{
    int location;
    int minDistanceToHome = BOARD_SIZE + 1;
    int best_redpiece = -1;

    // checking every possible outcome after roll dice for 4 piece
    for (int h = 0; h < TOTAL_PLAYERS; h++)
    {
        if (players[First_player].pieces[h].home_straight == 1)
        {
            continue; // if it is gone to homestraight continue
        }
        if (players[First_player].pieces[h].base == 1)
        { // checking piece is active
            if (players[First_player].pieces[h].rotation == 1)
            { // clockwise rotation ekk nm
                location = players[First_player].pieces[h].approach + (rollvalue * players[First_player].pieces[h].movement_speed);
                // checking piece 1 piece 2 piece 3 piece4 location
            }
            else
            { // anticlockwise
                location = players[First_player].pieces[h].approach - (rollvalue * players[First_player].pieces[h].movement_speed);
            }
        }
        else
        {
            best_redpiece = -1; // piece in base
        }
        for (int i = 0; i < TOTAL_PLAYERS; i++)
        {
            if (i == First_player)
                continue; // Skip the current player

            for (int j = 0; j < PIECES_for_PLAYER; j++)
            {
                int otherlocation = players[i].pieces[j].approach;
                if (otherlocation == location)
                {
                    // red can capture one piece
                    int distanceToHome = BOARD_SIZE - location;
                    if (distanceToHome < minDistanceToHome)
                    {
                        minDistanceToHome = distanceToHome; // find the closest one to home
                        best_redpiece = h;
                        // printf("\n%d\n ",best_redpiece+1);//print the red piece that can capture
                    }
                }
            }
        }
    }

    // RED PLAYER has captured something
    /*  for (int k = 0; k < TOTAL_PLAYERS; k++) {
     if(players[First_player].pieces[k].capture==1){
     return k;

     */

    return best_redpiece; // weradi
}

int green_AI(void)
{ // checking every possible wa
    int best_green_piece = -1;
    if (rollvalue == 6)
    {
        return -1;
        // always keep an empty base
    }
    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (players[First_player].pieces[i].base && players[First_player].pieces[i].home_straight == 0)
        {
            if (players[First_player].pieces[i].rotation)
            {
                int loc = players[First_player].pieces[i].approach + (rollvalue * players[First_player].pieces[i].movement_speed);

                for (int j = 0; j < TOTAL_PLAYERS; j++)
                { // check all the possibilities
                    if (loc == players[First_player].pieces[j].approach)
                    {
                        best_green_piece = i;
                       
                        // players[First_player].pieces[j].block.active=1;
                        //   players[First_player].pieces[i].block.active=1;
                    }
                }
            }
            else
            { // anticlockwise

                int loc = players[First_player].pieces[i].approach - (rollvalue * players[First_player].pieces[i].movement_speed);
                for (int j = 0; j < TOTAL_PLAYERS; j++)
                { // check all the possibilities
                    if (loc == players[First_player].pieces[j].approach)
                    {
                        best_green_piece = i;
                        
                        // players[First_player].pieces[j].block.active=1;
                        // players[First_player].pieces[i].block.active=1;
                    }
                }
            }
        }
    }
    return best_green_piece;
}
int yellow_AI(void)
{
    int location;
    int not_done = 0;
    int minDistanceToHome = BOARD_SIZE + 1;
    int best_yellow_piece = -1;

    for (int h = 0; h < TOTAL_PLAYERS; h++)
    {
        if (players[First_player].pieces[h].home_straight == 1)
        {
            continue; // if it is gone to homestraight continue
        }
        if (players[First_player].pieces[h].base == 1)
        { // checking piece is active
            if (players[First_player].pieces[h].rotation == 1)
            { // clockwise rotation
                location = players[First_player].pieces[h].approach + (rollvalue * players[First_player].pieces[h].movement_speed);
                // checking piece 1 piece 2 piece 3 piece4 location
            }
            else
            { // anticlockwise
                location = players[First_player].pieces[h].approach - (rollvalue * players[First_player].pieces[h].movement_speed);
            }
        }
        else
        {
            if (rollvalue == 6)
            {
                return h;
                // always keep an empty base
            }
            best_yellow_piece = -1; // no piece to move
        }
        // checking for captures
        for (int i = 0; i < TOTAL_PLAYERS; i++)
        {
            if (i == First_player)
            {
                continue; // Skip the current player
            }

            for (int j = 0; j < PIECES_for_PLAYER; j++)
            {
                if (players[i].pieces[j].base == 1 && players[i].pieces[j].home_straight == 0)
                {
                    int otherlocation = players[i].pieces[j].approach;
                    if (otherlocation == location)
                    {
                        best_yellow_piece = h;
                    }
                    else
                    {
                        not_done = 1;
                    }
                }
            }
        }
        if (not_done == 1 && players[First_player].pieces[h].base == 1 )
        {
            int loc_piece = players[First_player].pieces[h].approach;
            int distanceToHome = BOARD_SIZE - loc_piece;
            if (distanceToHome < minDistanceToHome)
            {
                minDistanceToHome = distanceToHome;
                best_yellow_piece = h;
            }
        }
    }
    return best_yellow_piece;
}
int Blue_AI(int piece_index)
{
    int location = -1;
    int best_blue_piece = -1;
    int not_done = 0;

    for (int h = 0; h < TOTAL_PLAYERS; h++)
    {
        if (players[First_player].pieces[h].home_straight == 1)
        {
            continue; // if it is gone to homestraight continue
        }
        if (players[First_player].pieces[h].base == 1)
        { // checking piece is active
            if (players[First_player].pieces[h].rotation == 1)
            { // clockwise rotation
                location = players[First_player].pieces[h].approach + (rollvalue * players[First_player].pieces[h].movement_speed);
                // checking piece 1 piece 2 piece 3 piece4 location
            }
            else
            { // anticlockwise
                location = players[First_player].pieces[h].approach - (rollvalue * players[First_player].pieces[h].movement_speed);
            }
            if (location == mystery_cell)
            {
                best_blue_piece = h;
            }
            else
            {
                not_done = 1;
            }
            
            if (not_done == 1 )
            {
                if (piece_index == -1)
                {
                    continue;
                }
                else
                {
                    best_blue_piece = (piece_index + 1)% TOTAL_PLAYERS; // cyclic manner in blue ai
                    if(players[First_player].pieces[best_blue_piece].home_straight==1 || players[First_player].pieces[best_blue_piece].base==0){
                        best_blue_piece = -1;
                    }
                }
            }
        }
        else
        {

            best_blue_piece = -1; // no piece to move
        }
        
        
    }
    return best_blue_piece;
}

int block(int piece_index)
{
    // int block_size = 0;
    int clockwise_count = 0, anticlockwise_count = 0;
    int max_distance_clockwise = -1, max_distance_anticlockwise = -1;
    if (players[First_player].pieces[piece_index].base && players[First_player].pieces[piece_index].home_straight == 0)
    {

        int loc = players[First_player].pieces[piece_index].approach;

        for (int j = 0; j < TOTAL_PLAYERS; j++)
        { // check all the possibilities
            if (j == piece_index)
            {
                continue;
            }
            if (loc == players[First_player].pieces[j].approach && players[First_player].pieces[j].base && players[First_player].pieces[j].home_straight == 0)
            {
                if (players[First_player].block.size == 4)
                {
                    break;
                }
                if (!players[First_player].pieces[j].block_active)
                {
                    players[First_player].block.block_pieces[players[First_player].block.size] = j; // storing number of the pieces that created the block
                    players[First_player].block.size++;
                }
                if (!players[First_player].pieces[piece_index].block_active)
                {
                    players[First_player].block.block_pieces[players[First_player].block.size] = piece_index; // storing the pieces in
                    players[First_player].block.size++;
                }

                players[First_player].pieces[j].block_active = 1;

                players[First_player].pieces[piece_index].block_active = 1;

                players[First_player].block.active = 1;

                // players[First_player].block_number++; //no.of pieces in the block

                if (players[First_player].pieces[piece_index].rotation != players[First_player].pieces[j].rotation)
                {

                    int distance_from_home;
                    if (players[First_player].pieces[j].rotation)
                    { // Clockwise
                        clockwise_count++;
                        distance_from_home = players[First_player].pieces[j].approach;
                        if (distance_from_home > max_distance_clockwise)
                        {
                            max_distance_clockwise = distance_from_home;
                        }
                    }
                    else
                    { // Anticlockwise
                        anticlockwise_count++;
                        distance_from_home = BOARD_SIZE - players[First_player].pieces[j].approach;
                        if (distance_from_home > max_distance_anticlockwise)
                        {
                            max_distance_anticlockwise = distance_from_home;
                        }
                    }
                }
                else
                {
                    players[First_player].block.block_rotation = players[First_player].pieces[piece_index].rotation;
                    // players[First_player].pieces[j].block.block_rotation=players[First_player].pieces[j].rotation;
                }
            }
        }
        // players[First_player].block.size=block_size;

        if (players[First_player].block.size >= 2)
        {
            // Determine block rotation based on the longest distance from home
            if (max_distance_clockwise > max_distance_anticlockwise)
            {
                players[First_player].block.block_rotation = 1; // Clockwise
            }
            else
            {                                                   // we should put struct block in player struct
                players[First_player].block.block_rotation = 0; // Anticlockwise
            }
        }
    }
    if (players[First_player].block.size > 0)
    {
        printf("\n");
        PlayerColour(First_player);
        printf(" has a block made using ");
        int size = players[First_player].block.size;
        for (int i = 0; i < size; i++)
        {
            int piece = players[First_player].block.block_pieces[i];
            printf("%d,", piece + 1);
        }
        printf("\n\n");
    }

    return 0;
}

void break_block(void)
{
    int size = players[First_player].block.size;
    int random_values[size];
    int remaining_distance = 6;
    int moved_distance;
    for (int i = 0; i < size; i++)
    {
        int piece_num = players[First_player].block.block_pieces[i];

        players[First_player].pieces[piece_num].block_active = 0; // block breaks

        players[First_player].block.size = 0;
        players[First_player].block.active = 0;
        players[First_player].block.block_capture = 0;

        // players[First_player].pieces[piece_num].approach
        random_values[i] = (rand() % 5) + 1;
        rollvalue = random_values[i];
        move_piece(piece_num);

        moved_distance = remaining_distance - random_values[i];
    }
}
int going_in_to_HomeStraight(int piece_index)
{
    if (players[First_player].pieces[piece_index].home_straight == 1)
    {
        int Location_in_home_straight = players[First_player].pieces[piece_index].home_straight_position;
        players[First_player].pieces[piece_index].home_straight_position += rollvalue;

        if (players[First_player].pieces[piece_index].home_straight_position > 6)
        {
            players[First_player].pieces[piece_index].home_straight_position = Location_in_home_straight;
            return -1;
        }
        else
        {
            PlayerColour(First_player);
            printf("'s piece %d is in the home straight and it moves to %d in home straight\n", piece_index + 1, players[First_player].pieces[piece_index].home_straight_position);
        }
        if (players[First_player].pieces[piece_index].home_straight_position == 6)
        {
            PlayerColour(First_player);
            printf("'s piece %d has come to HOME\n\n", piece_index + 1);
            players[First_player].pieces[piece_index].home_end = 1;
        }
    }
    return 0;
}
