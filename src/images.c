#include <fileioc.h>
#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"

void extract_sprites(gfx_sprite_t* sprites[SPRITE_COUNT])
{
    uint8_t slot;

    ti_CloseAll();
    slot = ti_Open("SpherixS", "r");
    if (!slot)
        handle_error("Missing Appvars");
    
    uint8_t* spr_ptr = ti_GetDataPtr(slot);

    sprites[0] = (gfx_sprite_t*)spr_ptr; // spherix
    spr_ptr += 1026;
    sprites[1] = (gfx_sprite_t*)spr_ptr; // gem
    spr_ptr += 258;
    sprites[2] = (gfx_sprite_t*)spr_ptr; // key
    spr_ptr += 258;
    sprites[3] = (gfx_sprite_t*)spr_ptr; // x mark
    spr_ptr += 258;
    sprites[4] = (gfx_sprite_t*)spr_ptr; // check mark

    ti_CloseAll();
}

void extract_tiles(gfx_sprite_t* tileset_tiles[TILE_COUNT])
{
	ti_CloseAll();
	uint8_t slot = ti_Open("SpherixT", "r");
	if (!slot)
		handle_error("Missing Appvars");

	uint16_t pal_size;
	uint16_t* pal_ptr;
	uint8_t* tmp_ptr;
	gfx_sprite_t** tiles = tileset_tiles;

	pal_ptr = (uint16_t*)ti_GetDataPtr(slot);
	pal_size = *pal_ptr;
	pal_ptr++;

	// set up the palette
	gfx_SetPalette(pal_ptr, pal_size, 0);
	tmp_ptr = (uint8_t*)pal_ptr;
	tmp_ptr += pal_size;

	// store tile pointers
	for (uint8_t i = 0; i < TILE_COUNT; i++)
	{
		tiles[i] = (gfx_sprite_t*)tmp_ptr;
		tmp_ptr += TILE_DATA_SIZE;
	}

	// close the open file
	ti_CloseAll();
}

void draw_sprites(pos_t player, pos_t map, gfx_sprite_t* sprites[SPRITE_COUNT])
{
    // draw sprites (player and boulders on buttons for now)
    // boulders not on button tile is part of the tilemap

	uint16_t player_draw_x = TILE_WIDTH * (player.x - map.x) + TILEMAP_START_DRAW_X;
	uint8_t player_draw_y = TILE_HEIGHT * (player.y - map.y) + TILEMAP_START_DRAW_Y;

	gfx_TransparentSprite_NoClip(sprites[0], player_draw_x, player_draw_y);
}

void draw_background(void)
{
        gfx_SetColor(BLACK_COLOR);

		// Black borders around tilemap
	    gfx_FillRectangle_NoClip(0, 0, 320, 8); 
	    gfx_FillRectangle_NoClip(0, 232, 320, 8);
	    gfx_FillRectangle_NoClip(0, 0, 24, 240);
	    gfx_FillRectangle_NoClip(312, 0, 8, 240);
}