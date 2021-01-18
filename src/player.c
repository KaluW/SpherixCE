#include "defines.h"
#include "player.h"

bool pressed_f1 = false;
bool pressed_f2 = false;
bool pressed_f3 = false;
bool pressed_f4 = false;
bool pressed_f5 = false;

bool pressed_2nd = false;
bool pressed_Alpha = false;

bool pressed_down = false;
bool pressed_left = false;
bool pressed_right = false;
bool pressed_up = false;

bool allow_up_press = true;


void updatePlayer(void)
{
	uint8_t move = TILE_WIDTH;
	if (pressed_left)
		if (player.x)
			player.x -= move;

	if (pressed_right)
		if (player.x < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
			player.x += move;

	if (pressed_up)
		if (player.y)
			player.y -= move;

	if (pressed_down)
		if (player.y < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
			player.y += move;
}