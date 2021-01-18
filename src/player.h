#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <tice.h>

void updatePlayer(void);
bool isLegalMove(uint8_t x, uint8_t y);

extern bool pressed_f1;
extern bool pressed_f2;
extern bool pressed_f3;
extern bool pressed_f4;
extern bool pressed_f5;
extern bool pressed_2nd;
extern bool pressed_Alpha;
extern bool pressed_down;
extern bool pressed_left;
extern bool pressed_right;
extern bool pressed_up;

extern bool allow_up_press;


#endif