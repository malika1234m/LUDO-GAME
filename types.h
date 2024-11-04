#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_PLAYERS 4
#define BOARD_SIZE 52
#define NEGATIVE_BOARD_SIZE -52
#define PIECES_for_PLAYER 4

extern int First_player;
extern int mystery_cell;

extern int rollvalue;
extern int toss;


typedef struct
{
    int size;
    int block_rotation; // 0=anticlockwise
    // int block_movementspeed;
    // int block_homeactive;
    int block_capture;
    int active; // 0=not active
    int block_pieces[4];
    ;
} blocks;

typedef struct
{
    int position;
    int base;     // 0==base
    int capture;  // if piece capture a opponent piece
    int approach; // real location of the according to standard square id
    int rotation; // 0=anticlockwise
    // int aura;
    int movement_speed;
    int round;
    int home_straight;
    int home_straight_position;
    int home_end;
    int block_active;

} pawns;

typedef struct
{
    pawns pieces[4];
    int aura;
    int turns; // counting turns in auraaaaaaaaa
    // int block_number;
    // int block_pieces[4];
    blocks block;
    const char *color;

} player;
player players[4];
#endif