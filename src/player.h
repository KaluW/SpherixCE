#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <keypadc.h>
#include <graphx.h>

#include "defines.h"

typedef struct Keypad
{
    kb_key_t dir_press;

    bool pressed_2nd;
    bool pressed_Alpha;
    bool pressed_Clear; // exit
} keypad_t;

void handle_keypad(keypad_t* keypad);

typedef struct Player
{
    pos_t pos;
    directions_t facing;

    bool isPushingBoulder;

    keypad_t keypad;
} player_t;

void handle_keypad(keypad_t* keypad);
void updatePlayer(game_t* game, player_t* player);
bool isLegalMove(player_t* player, game_t* game);

#endif