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

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define TILE_DATA_SIZE TILE_WIDTH * TILE_HEIGHT + 2

#define TILEMAP_WIDTH 12
#define TILEMAP_HEIGHT 9

#define TILEMAP_DRAW_WIDTH 9
#define TILEMAP_DRAW_HEIGHT 7

#define TILEMAP_DRAW_OFFSET_X 24
#define TILEMAP_DRAW_OFFSET_Y 8

#endif