#ifndef DEFINES_H
#define DEFINES_H

#include <graphx.h>

#define TILE_COUNT 12

#define TILE_EMPTY 0

void missing_appvars(void);

extern gfx_tilemap_t tilemap;

typedef struct
{
	uint8_t level;
	bool exit;
} game_t;

extern game_t game;

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define TILE_DATA_SIZE TILE_WIDTH * TILE_HEIGHT + 2

#define TILEMAP_WIDTH 12
#define TILEMAP_HEIGHT 10

#define TILEMAP_DRAW_WIDTH 10
#define TILEMAP_DRAW_HEIGHT 7

#endif