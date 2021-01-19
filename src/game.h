#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <tice.h>

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

void handle_2nd_press(uint8_t x, uint8_t y);
void handle_boulder(uint8_t x, uint8_t y);
void handle_key(uint8_t x, uint8_t y);
void handle_gem(uint8_t x, uint8_t y);
void updatePlayer(void);
bool isLegalMove(uint8_t x, uint8_t y);

typedef enum directions { up, down, left, right } directions_t;
extern directions_t direction;

typedef struct
{
	uint8_t level;
	bool exit;

	// draw map at these coords
	uint8_t map_x;
	uint8_t map_y;

	// player @ (map_x + scroll_to_x, map_y + scroll_to_y)
	uint8_t scroll_to_x;
	uint8_t scroll_to_y;

	directions_t playerFacing;

	uint8_t keys;
	bool hasGem;
} game_t;

extern game_t game;





#endif