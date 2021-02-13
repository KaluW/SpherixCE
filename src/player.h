#ifndef PLAYER_H
#define PLAYER_H

#include <graphx.h>
#include <keypadc.h>
#include <stdint.h>

#include "defines.h" 

typedef struct Keypad
{
    kb_key_t dir_press;
    kb_key_t prev_press;
    bool allow_down_press; // rising edge detector
    bool pressed_down;

    bool pressed_2nd; // interact with onscreen items
    bool pressed_Alpha;
    bool pressed_Clear; // exit
} keypad_t;

typedef enum Directions
{
    up,
    down,
    left,
    right
} directions_t;

typedef struct Player
{
    pos_t pos;
    directions_t facing;

    bool isPushingBoulder;

    keypad_t keypad;
} player_t;
extern player_t player;

void handle_keypad(void);
void update_player(void);

#endif