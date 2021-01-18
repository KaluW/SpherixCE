#include <graphx.h>
#include <fileioc.h>

#include "graphics.h"
#include "defines.h"
#include "player.h"

gfx_sprite_t* tileset_tiles[TILE_COUNT];
gfx_sprite_t* spherix;

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

void extract_sprites(void) {
	uint8_t slot;

	ti_CloseAll();
	slot = ti_Open("SpherixS", "r");
	if (!slot)
		missing_appvars();

	uint8_t* spr_ptr = ti_GetDataPtr(slot);
	spherix = (gfx_sprite_t*)spr_ptr;

	ti_CloseAll();
}

void updateMap(void)
{
	gfx_TransparentTilemap(&tilemap, player.x, player.y);
	gfx_FillRectangle(0, 0, 320, 16);
	gfx_PrintStringXY("x offset:", 48, 4);
<<<<<<< HEAD
	gfx_PrintUInt(game.map_x + game.scroll_to_x, 2);
=======
	gfx_PrintUInt(player.x, 3);
>>>>>>> parent of 07aec4d... Implemented player movement
	gfx_PrintString(" y offset:");
	gfx_PrintUInt(player.y, 2);
}