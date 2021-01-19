#include "data.h"
#include "defines.h"
#include "graphics.h"

unsigned char level_map[TILEMAP_WIDTH * TILEMAP_HEIGHT];

tiles_t data_map[TILEMAP_WIDTH * TILEMAP_HEIGHT] = {
		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,
		wall,		floor,		floor,		wall,		floor,		floor,		wall,		_gem,		hole,		_key,		floor,		wall,
		wall,		floor,		floor,		floor,		floor,		floor,		wall,		hole,		hole,		floor,		floor,		wall,
		wall,		wall,		wall,		wall,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		wall,
		wall,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		wall,
		wall,		floor,		chest_b,	floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		wall,
		wall,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		wall,
		wall,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		floor,		end,		wall,
		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,		wall,
};

void create_tilemap(void) {

	tiles_t* in;
	unsigned char* out;

	for (uint8_t row = 0; row < TILEMAP_HEIGHT; row++)
	{
		for (uint8_t col = 0; col < TILEMAP_WIDTH; col++)
		{
			in = &data_map[row * TILEMAP_WIDTH + col];
			out = &level_map[row * TILEMAP_WIDTH + col];

			if (*in == floor)
				*out = FLOOR_TILE;
			
			if (*in == wall || (*in >= fWall_1 && *in <= fWall_5) ) // if it's a type of wall, output a wall
				*out = WALL_TILE;
			
			if (*in == hole)
				*out = HOLE_TILE;

			if (*in == _key)
				*out = KEY_TILE;

			if (*in == end)
				*out = END_TILE;

			if (*in == water)
				*out = WATER_TILE;

			if (*in == _gem)
				*out = GEM_TILE;

			if (*in == boulder)
				*out = BOULDER_TILE;

			if (*in >= button_1 && *in <= button_5)
				*out = BUTTON_TILE;

			if (*in >= up_lad_1 && *in <= up_lad_5)
				*out = UP_LADDER_TILE;

			if (*in >= dn_lad_1 && *in <= dn_lad_5)
				*out = DOWN_LADDER_TILE;

			if (*in == chest_b || *in == chest_g || *in == chest_k)
				*out = CHEST_TILE;
		}
	}
}