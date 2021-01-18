#include "defines.h"
#include "graphics.h"

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

bool isLegalMove(uint8_t x, uint8_t y) {

	return (*gfx_TilePtrMapped(&tilemap, x, y) == FLOOR_TILE);

}

void updatePlayer(void)
{
	uint8_t right_bound = TILEMAP_WIDTH;
	uint8_t bottom_bound = TILEMAP_HEIGHT;

	uint8_t center_x = TILEMAP_DRAW_WIDTH / 2;
	uint8_t center_y = TILEMAP_DRAW_HEIGHT / 2;

	uint8_t player_x = game.map_x + game.scroll_to_x;
	uint8_t player_y = game.map_y + game.scroll_to_y;

	if (pressed_left)
	{
		if (!isLegalMove(player_x - 1, player_y)) return;

		// move the player instead of the map if tilemap drawn to its edge
		if (game.map_x) {
			// move the player instead of the map if the player isn't at the middle of the screen
			if (game.scroll_to_x > center_x) {
				game.scroll_to_x--;
			}
			else {
				game.map_x--;
			}
		}
		else if (game.scroll_to_x) {
			game.scroll_to_x--;
		}

		return; // don't check multiple key inputs
	}
	
	if (pressed_right)
	{
		if (!isLegalMove(player_x + 1, player_y)) return;

		if (game.map_x + TILEMAP_DRAW_WIDTH < right_bound) {
			if (game.scroll_to_x < center_x) {
				game.scroll_to_x++;
			}
			else {
				game.map_x++;
			}
				
		}
		else if (game.map_x + game.scroll_to_x < right_bound - 1) {
			game.scroll_to_x++;
		}
	}
	else if (pressed_up)
	{
		if (!isLegalMove(player_x, player_y - 1)) return;

		if (game.map_y) {
			if (game.scroll_to_y > center_y) {
				game.scroll_to_y--;
			}
			else {
				game.map_y--;
			}
			
		}
		else if (game.scroll_to_y) {
			game.scroll_to_y--;
		}
	}
	else if (pressed_down)
	{
		if (!isLegalMove(player_x, player_y + 1)) return;

		if (game.map_y + TILEMAP_DRAW_HEIGHT < bottom_bound) {
			if (game.scroll_to_y < center_y) {
				game.scroll_to_y++;
			}
			else {
				game.map_y++;
			}
		}
		else if (game.map_y + game.scroll_to_y < bottom_bound - 1) {
			game.scroll_to_y++;
		}
	}
}