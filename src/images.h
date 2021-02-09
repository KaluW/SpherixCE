#ifndef IMAGES_H
#define IMAGES_H

#include <graphx.h>

#include "defines.h"
#include "player.h"

extern gfx_tilemap_t tilemap;
extern gfx_sprite_t *tileset_tiles[TILE_COUNT];

gfx_rletsprite_t* sprite_spherix;
gfx_rletsprite_t* sprite_gem;
gfx_rletsprite_t* sprite_key;
gfx_rletsprite_t* sprite_x_mark;
gfx_rletsprite_t* sprite_check;

void extract_sprites(void);
void extract_tiles(void);

void update_graphics(void);
void draw_background(void);

#endif