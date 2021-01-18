#include <graphx.h>
#include <fileioc.h>

#include "graphics.h"
#include "defines.h"
#include "player.h"

gfx_sprite_t* tileset_tiles[TILE_COUNT];

gfx_sprite_t* spherix;
gfx_sprite_t* gem;
gfx_sprite_t* key;
gfx_sprite_t* x_mark;
gfx_sprite_t* check_mark;

void extract_tiles(void)
{
	ti_CloseAll();
	uint8_t slot = ti_Open("SpherixT", "r");
	if (!slot)
		missing_appvars();

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

void extract_sprites(void)
{
    uint8_t slot;

    ti_CloseAll();
    slot = ti_Open("SpherixS", "r");
    if (slot) {
        uint8_t* spr_ptr = ti_GetDataPtr(slot);

        spherix = (gfx_sprite_t*)spr_ptr;
        spr_ptr += 1026;
        gem = (gfx_sprite_t*)spr_ptr;
        spr_ptr += 258;
        key = (gfx_sprite_t*)spr_ptr;
        spr_ptr += 258;
        x_mark= (gfx_sprite_t*)spr_ptr;
        spr_ptr += 258;
        check_mark = (gfx_sprite_t*)spr_ptr;
    }
    else {
        missing_appvars();
    }

    ti_CloseAll();
}

void updateMap(void)
{
	gfx_SetColor(1);

	gfx_SetTextFGColor(0);
	gfx_SetTextBGColor(1);

	gfx_SetMonospaceFont(8);

	gfx_TransparentTilemap_NoClip(&tilemap, game.map_x * TILE_WIDTH, game.map_y * TILE_HEIGHT);

	gfx_FillRectangle_NoClip(0, 0, 320, 8); // Top
	gfx_FillRectangle_NoClip(0, 232, 320, 8); // bottom
	gfx_FillRectangle_NoClip(0, 0, 16, 240); // left 
	gfx_FillRectangle_NoClip(304, 0, 16, 240); //right

	/*
	gfx_PrintStringXY("x offset:", 48, 4);
	gfx_PrintUInt(game.map_x + game.scroll_to_x, 2);
	gfx_PrintString(" y offset:");
	gfx_PrintUInt(game.map_y + game.scroll_to_y, 2);
	*/

	uint16_t player_x = (game.scroll_to_x) * TILE_WIDTH + TILEMAP_DRAW_OFFSET_X;
	uint8_t player_y = (game.scroll_to_y) * TILE_HEIGHT + TILEMAP_DRAW_OFFSET_Y;

	gfx_TransparentSprite(spherix, player_x, player_y);
}