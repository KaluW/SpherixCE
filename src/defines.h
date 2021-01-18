#ifndef DEFINES_H
#define DEFINES_H

#include <graphx.h>

#define GRAY_COLOR 0
#define BLACK_COLOR 1
#define WHITE_COLOR 2



#define TILE_COUNT 12
#define TILE_EMPTY 0

void missing_appvars(void);

extern gfx_tilemap_t tilemap;

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
} game_t;

extern game_t game;

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define TILE_DATA_SIZE TILE_WIDTH * TILE_HEIGHT + 2

#define TILEMAP_WIDTH 12
#define TILEMAP_HEIGHT 9

#define TILEMAP_DRAW_WIDTH 9
#define TILEMAP_DRAW_HEIGHT 7

#define TILEMAP_DRAW_OFFSET_X 16
#define TILEMAP_DRAW_OFFSET_Y 8

#endif