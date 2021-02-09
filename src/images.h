#ifndef IMAGES_H
#define IMAGES_H

#include <graphx.h>

#include "defines.h"
#include "player.h"

extern gfx_tilemap_t tilemap;
extern gfx_sprite_t *tileset_tiles[TILE_COUNT];

extern gfx_rletsprite_t* sprite_spherix;
extern gfx_rletsprite_t* sprite_gem;
extern gfx_rletsprite_t* sprite_key;
extern gfx_rletsprite_t* sprite_x_mark;
extern gfx_rletsprite_t* sprite_check;

extern gfx_rletsprite_t* sprite_arrows[4];

void extract_sprites(void);
void extract_tiles(void);

#endif