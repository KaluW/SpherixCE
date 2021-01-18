#include <graphx.h>
#include <keypadc.h>

#include "defines.h"
#include "graphics.h"
#include "player.h"

game_t game;

gfx_tilemap_t tilemap;
unsigned char level_map[TILEMAP_WIDTH * TILEMAP_HEIGHT] = { 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 1, 6, 2, 3, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1,
	1, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
}; 

void missing_appvars(void)
{
	gfx_End();
	os_SetCursorPos(0, 0);
	os_PutStrFull("Err: Missing AppVars");
	while (!os_GetCSC());
	exit(0);
}

void handle_keypad(void)
{

	bool press_up;
	kb_key_t g1_key, g2_key, g6_key, g7_key;

	kb_Scan();

	// read keypad data
	g1_key = kb_Data[1];
	g2_key = kb_Data[2];
	g6_key = kb_Data[6];
	g7_key = kb_Data[7];

	pressed_f1 = (g1_key & kb_Yequ);
	pressed_f2 = (g1_key & kb_Window);
	pressed_f3 = (g1_key & kb_Zoom);
	pressed_f4 = (g1_key & kb_Trace);
	pressed_f5 = (g1_key & kb_Graph);

	pressed_2nd = (g1_key & kb_2nd);
	pressed_Alpha = (g2_key & kb_Alpha);

	pressed_down = (g7_key & kb_Down);
	pressed_left = (g7_key & kb_Left);
	pressed_right = (g7_key & kb_Right);
	press_up = (g7_key & kb_Up);

	// establishing the existence of gravity
	if (allow_up_press) {
		pressed_up = press_up;
	}
	else if (!press_up) {
		allow_up_press = true;
	}

	if (g6_key & kb_Clear)
		game.exit = true;
}

void init_game(void)
{
	tilemap.map = level_map;
	tilemap.tiles = tileset_tiles;
	tilemap.type_width = gfx_tile_32_pixel;
	tilemap.type_height = gfx_tile_32_pixel;
	tilemap.tile_height = TILE_HEIGHT;
	tilemap.tile_width = TILE_WIDTH;
	tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
	tilemap.draw_width = TILEMAP_DRAW_WIDTH;
	tilemap.width = TILEMAP_WIDTH;
	tilemap.height = TILEMAP_HEIGHT;
	tilemap.y_loc = TILEMAP_DRAW_OFFSET_Y;
	tilemap.x_loc = TILEMAP_DRAW_OFFSET_X;

	game.map_x = 0;
	game.map_y = 0;

	game.scroll_to_x = 1;
	game.scroll_to_y = 1;

	gfx_FillScreen(1);


}

void main(void)
{
	srand(rtc_Time());
	gfx_Begin();

	extract_tiles();
	extract_sprites();

	init_game();

	gfx_SetDrawBuffer();

	while (!game.exit)
	{
		handle_keypad();

		updatePlayer();
		updateMap();

		gfx_SwapDraw();
	}

	gfx_End();
}