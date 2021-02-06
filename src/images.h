#ifndef IMAGES_H
#define IMAGES_H

#include <graphx.h>

#include "defines.h"

void extract_sprites(gfx_sprite_t* sprites[SPRITE_COUNT]);
void extract_tiles(gfx_sprite_t* tilest_tiles[TILE_COUNT]);

void draw_sprites(pos_t player, pos_t map, gfx_sprite_t* sprites[SPRITE_COUNT]);
void draw_background(void);

#endif