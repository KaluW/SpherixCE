#ifndef PLAYER_H
#define PLAYER_H

#include <graphx.h>
#include <keypadc.h>
#include <stdint.h>

#include "defines.h"

typedef struct Player
{
    pos_t pos;
    directions_t facing;

    bool isPushingBoulder;

    keypad_t keypad;
} player_t;
extern player_t player;

void handle_keypad(void);
void handle_keypad(void);
void update_player(void);
bool isLegalMove(void);

#endif