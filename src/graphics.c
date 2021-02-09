#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"
#include "graphics.h"

void update_graphics(void)
{
    uint16_t mapDrawX = game.mapPos.x * TILE_WIDTH;
    uint8_t mapDrawY = game.mapPos.y * TILE_HEIGHT;

    uint16_t playerDrawX = TILE_WIDTH * (player.pos.x - game.mapPos.x) + TILEMAP_START_DRAW_X;
    uint8_t playerDrawY = TILE_HEIGHT * (player.pos.y - game.mapPos.y) + TILEMAP_START_DRAW_Y;

    gfx_Tilemap_NoClip(&tilemap, mapDrawX, mapDrawY);
    gfx_RLETSprite_NoClip(sprite_spherix, playerDrawX, playerDrawY);
}

#define TEXT_SPACING 20
#define START_TEXT_Y TILE_HEIGHT / 2

void draw_background(uint16_t frametime)
{
    gfx_SetColor(BLACK_COLOR);

    // Black borders around tilemap
    gfx_FillRectangle_NoClip(0, 0, 320, 8); 
    gfx_FillRectangle_NoClip(0, 232, 320, 8);
    gfx_FillRectangle_NoClip(0, 0, 24, 240);
    gfx_FillRectangle_NoClip(312, 0, 8, 240);

    gfx_SetTextFGColor(TRANSPARENT_GRAY);
	gfx_SetTextBGColor(BLACK_COLOR);
	
    const uint8_t drawX = (TILEMAP_START_DRAW_X - sprite_arrows[0]->width) / 2;

    _display_key_info(drawX);
    _display_endGem_info(drawX);

    _display_lower(drawX, frametime);
}

void _display_key_info(uint8_t drawX)
{
    gfx_RLETSprite_NoClip(sprite_key, drawX, START_TEXT_Y);
	gfx_SetTextXY(drawX, START_TEXT_Y + TEXT_SPACING);
	gfx_PrintUInt(game.numKeys, 1);

	gfx_SetColor(WHITE_COLOR);
	gfx_HorizLine_NoClip(drawX, START_TEXT_Y + TEXT_SPACING * 2 - TILE_HEIGHT / 4, sprite_gem->width);
}

void _display_endGem_info(uint8_t drawX)
{
	gfx_RLETSprite_NoClip(sprite_gem, drawX, START_TEXT_Y + TEXT_SPACING * 2);
	if (!game.hasEndGem) {
		gfx_RLETSprite_NoClip(sprite_x_mark, drawX, START_TEXT_Y + TEXT_SPACING * 3);
	}
	else {
		gfx_RLETSprite_NoClip(sprite_check, drawX, START_TEXT_Y + TEXT_SPACING * 3);
	}
}

void _display_lower(uint8_t drawX, uint16_t frametime)
{
    const uint8_t drawY = LCD_HEIGHT - sprite_arrows[0]->height - drawX;

    gfx_SetTextFGColor(WHITE_COLOR);

    gfx_PrintUIntXY(32768 / frametime, 2, drawX, drawY - 3 * sprite_arrows[0]->height / 4);

    gfx_RLETSprite_NoClip(sprite_arrows[player.facing], drawX, drawY);
}