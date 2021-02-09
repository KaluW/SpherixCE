#include <fileioc.h>
#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"
#include "player.h"
#include "tile_handlers.h"

void extract_sprites(gfx_rletsprite_t* sprites[SPRITE_COUNT])
{
    uint8_t slot;

    ti_CloseAll();
    slot = ti_Open("SpherixS", "r");
    if (!slot)
        handle_error("Missing Appvars");
    
    uint8_t* spr_ptr = ti_GetDataPtr(slot);

    sprites[0] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr); // spherix
    spr_ptr += 1026;
    sprites[1] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr); // gem
    spr_ptr += 258;
    sprites[2] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr); // key
    spr_ptr += 258;
    sprites[3] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr); // x mark
    spr_ptr += 258;
    sprites[4] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr); // check mark

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

void update_graphics(player_t player, game_t game, gfx_rletsprite_t* sprites[SPRITE_COUNT])
{
    uint16_t mapDrawX = game.mapPos.x * TILE_WIDTH;
    uint8_t mapDrawY = game.mapPos.y * TILE_HEIGHT;

    uint16_t playerDrawX = TILE_WIDTH * (player.pos.x - game.mapPos.x) + TILEMAP_START_DRAW_X;
    uint8_t playerDrawY = TILE_HEIGHT * (player.pos.y - game.mapPos.y) + TILEMAP_START_DRAW_Y;

    gfx_TransparentTilemap_NoClip(&game.tile_map, mapDrawX, mapDrawY);
    gfx_RLETSprite_NoClip(sprites[SPRITE_SPHERIX], playerDrawX, playerDrawY);
}

void draw_background(game_t game, gfx_rletsprite_t* sprites[SPRITE_COUNT])
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
	
	gfx_RLETSprite_NoClip(sprites[SPRITE_KEY], 4, 16);
	gfx_SetTextXY(4, 36);
	gfx_PrintUInt(game.numKeys, 1);

	gfx_SetColor(WHITE_COLOR);
	gfx_HorizLine_NoClip(4, 52, 16);

	gfx_RLETSprite_NoClip(sprites[SPRITE_GEM], 4, 56);
	if (!game.hasEndGem) {
		gfx_RLETSprite_NoClip(sprites[SPRITE_X_MARK], 4, 76);
	}
	else {
		gfx_RLETSprite_NoClip(sprites[SPRITE_CHECK], 4, 76);
	}
}