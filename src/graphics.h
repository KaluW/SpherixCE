#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <graphx.h>

#include "defines.h"

#define FLOOR_TILE 0
#define WALL_TILE 1
#define HOLE_TILE 2
#define KEY_TILE 3
#define END_TILE 4
#define WATER_TILE 5
#define GEM_TILE 6
#define BOULDER_TILE 7
#define BUTTON_TILE 8
#define UP_LADDER_TILE 9
#define DOWN_LADDER_TILE 10
#define CHEST_TILE 11

extern gfx_sprite_t* tileset_tiles[TILE_COUNT];

extern gfx_sprite_t* spherix;
extern gfx_sprite_t* gem;
extern gfx_sprite_t* key;
extern gfx_sprite_t* x_mark;
extern gfx_sprite_t* check_mark;

void extract_tiles(void);
void extract_sprites(void);

void updateMap(void);

#endif