#include "data.h"
#include "defines.h"
#include "game.h"
#include "graphics.h"

bool pressed_2nd = false;
bool pressed_Alpha = false;

bool pressed_down = false;
bool pressed_left = false;
bool pressed_right = false;
bool pressed_up = false;

directions_t direction;

void handle_2nd_press(uint8_t x, uint8_t y)
{
	uint8_t test_x = x;
	uint8_t test_y = y;

	if (game.playerFacing == up) { test_y = y - 1; }
	if (game.playerFacing == down) { test_y = y + 1; }
	if (game.playerFacing == left) { test_x = x - 1; }
	if (game.playerFacing == right) { test_x = x + 1; }

	tiles_t* test_tile_value = &data_map[test_y * TILEMAP_WIDTH + test_x];

	// this chest apparently has a literal boulder inside of it?
	if (*test_tile_value == chest_b) 
	{
		gfx_SetTileMapped(&tilemap, test_x, test_y, BOULDER_TILE);
		data_map[test_y * TILEMAP_WIDTH + test_x] = boulder;
		game.keys--;
		return;
	}

	if (*test_tile_value == chest_g)
	{
		gfx_SetTileMapped(&tilemap, test_x, test_y, FLOOR_TILE);
		data_map[test_y * TILEMAP_WIDTH + test_x] = floor;
		game.hasGem = true;
		game.keys--;
		return;
	}

	if (*test_tile_value == chest_k)
	{
		gfx_SetTileMapped(&tilemap, test_x, test_y, FLOOR_TILE);
		data_map[test_y * TILEMAP_WIDTH + test_x] = floor;
		return;
	}

}

void handle_key(uint8_t x, uint8_t y)
{
	gfx_SetTileMapped(&tilemap, x, y, FLOOR_TILE);
	data_map[y * TILEMAP_WIDTH + x] = floor;

	game.keys++;
}

void handle_gem(uint8_t x, uint8_t y)
{
	gfx_SetTileMapped(&tilemap, x, y, FLOOR_TILE);
	data_map[y * TILEMAP_WIDTH + x] = floor;

	game.hasGem = true;
}

void handle_boulder(uint8_t x, uint8_t y)
{
	uint8_t test_x = x;
	uint8_t test_y = y;

	if (game.playerFacing == up) { test_y = y - 1; }
	if (game.playerFacing == down) { test_y = y + 1; }
	if (game.playerFacing == left) { test_x = x - 1; }
	if (game.playerFacing == right) { test_x = x + 1; }

	tiles_t* curr_tile_value = &data_map[y * TILEMAP_WIDTH + x];
	tiles_t* test_tile_value = &data_map[test_y * TILEMAP_WIDTH + test_x];

	// move boulder to new floor tile. Replace old boulder tile with floor tile.
	if (*test_tile_value == floor)
	{
		gfx_SetTileMapped(&tilemap, x, y, FLOOR_TILE);
		gfx_SetTileMapped(&tilemap, test_x, test_y, BOULDER_TILE);

		*curr_tile_value = floor;
		*test_tile_value = boulder;
	}

	// replace hole with new floor tile. Replace old boulder tile with floor tile
	if(*test_tile_value == hole)
	{
		gfx_SetTileMapped(&tilemap, x, y, FLOOR_TILE);
		gfx_SetTileMapped(&tilemap, test_x, test_y, FLOOR_TILE);

		*curr_tile_value = floor;
		*test_tile_value = floor;
	}
}

bool isLegalMove(uint8_t x, uint8_t y)
{
	uint8_t test_x = x;
	uint8_t test_y = y;

	if (game.playerFacing == up) { test_y = y - 1; }
	if (game.playerFacing == down) { test_y = y + 1; }
	if (game.playerFacing == left) { test_x = x - 1; }
	if (game.playerFacing == right) { test_x = x + 1; }

	uint8_t test_tile_value = data_map[test_y * TILEMAP_WIDTH + test_x];

	if (test_tile_value == boulder) handle_boulder(test_x, test_y);
	if (test_tile_value == _key) handle_key(test_x, test_y);
	if (test_tile_value == _gem) handle_gem(test_x, test_y);

	if (test_tile_value == end) 
		if (game.hasGem) {
			// you won
			gfx_End();
			exit(0);
		}

	return (test_tile_value == floor);

}

void updatePlayer(void)
{
	uint8_t right_bound = TILEMAP_WIDTH;
	uint8_t bottom_bound = TILEMAP_HEIGHT;

	uint8_t center_x = TILEMAP_DRAW_WIDTH / 2;
	uint8_t center_y = TILEMAP_DRAW_HEIGHT / 2;

	uint8_t player_x = game.map_x + game.scroll_to_x;
	uint8_t player_y = game.map_y + game.scroll_to_y;

	if (pressed_2nd)
		handle_2nd_press(player_x, player_y);

	if (pressed_left)
	{
		game.playerFacing = left;
		if (!isLegalMove(player_x, player_y)) return;

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
		game.playerFacing = right;
		if (!isLegalMove(player_x, player_y)) return;

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

		return;
	}

	if (pressed_up)
	{
		game.playerFacing = up;
		if (!isLegalMove(player_x, player_y)) return;

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

		return;
	}

	if (pressed_down)
	{
		game.playerFacing = down;
		if (!isLegalMove(player_x, player_y)) return;

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

		return;
	}
}