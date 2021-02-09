#include <fileioc.h>
#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"
#include "player.h"
#include "tile_handlers.h"

gfx_tilemap_t tilemap;
gfx_sprite_t *tileset_tiles[TILE_COUNT];

gfx_rletsprite_t* sprite_spherix;
gfx_rletsprite_t* sprite_gem;
gfx_rletsprite_t* sprite_key;
gfx_rletsprite_t* sprite_x_mark;
gfx_rletsprite_t* sprite_check;

void extract_sprites(void)
{
    uint8_t slot;

    ti_CloseAll();
    slot = ti_Open("SpherixS", "r");
    if (!slot)
        handle_error("Missing Appvars");
    
    uint8_t* spr_ptr = ti_GetDataPtr(slot);

    sprite_spherix = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 1026;
    sprite_gem = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_key = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_x_mark = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_check = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);

    ti_CloseAll();
}

void extract_tiles(void)
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

void update_graphics(void)
{
    uint16_t mapDrawX = game.mapPos.x * TILE_WIDTH;
    uint8_t mapDrawY = game.mapPos.y * TILE_HEIGHT;

    uint16_t playerDrawX = TILE_WIDTH * (player.pos.x - game.mapPos.x) + TILEMAP_START_DRAW_X;
    uint8_t playerDrawY = TILE_HEIGHT * (player.pos.y - game.mapPos.y) + TILEMAP_START_DRAW_Y;

    gfx_Tilemap_NoClip(&tilemap, mapDrawX, mapDrawY);
    gfx_RLETSprite_NoClip(sprite_spherix, playerDrawX, playerDrawY);
}

void draw_background(void)
{
    gfx_SetColor(BLACK_COLOR);

    // Black borders around tilemap
    gfx_FillRectangle_NoClip(0, 0, 320, 8); 
    gfx_FillRectangle_NoClip(0, 232, 320, 8);
    gfx_FillRectangle_NoClip(0, 0, 24, 240);
    gfx_FillRectangle_NoClip(312, 0, 8, 240);

    // Display objects in background

    gfx_SetTextFGColor(TRANSPARENT_GRAY);
	gfx_SetTextBGColor(BLACK_COLOR);
	
	gfx_RLETSprite_NoClip(sprite_key, 4, 16);
	gfx_SetTextXY(4, 36);
	gfx_PrintUInt(game.numKeys, 1);

	gfx_SetColor(WHITE_COLOR);
	gfx_HorizLine_NoClip(4, 52, 16);

	gfx_RLETSprite_NoClip(sprite_gem, 4, 56);
	if (!game.hasEndGem) {
		gfx_RLETSprite_NoClip(sprite_x_mark, 4, 76);
	}
	else {
		gfx_RLETSprite_NoClip(sprite_check, 4, 76);
	}
}