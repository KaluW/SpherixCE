#ifndef IMAGES_H
#define IMAGES_H

#include <graphx.h>

#include "defines.h"
#include "player.h"

void extract_sprites(gfx_rletsprite_t* sprites[SPRITE_COUNT]);
void extract_tiles(gfx_sprite_t* tilest_tiles[TILE_COUNT]);

void update_graphics(player_t player, game_t game, gfx_rletsprite_t* sprites[SPRITE_COUNT]);
void draw_background(game_t game, gfx_rletsprite_t* sprites[SPRITE_COUNT]);

#endif