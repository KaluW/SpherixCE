#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"
#include "graphics.h"

static void display_borders(void);
static void display_key_info(uint8_t index);
static void display_endGem_info(uint8_t index);
static void display_direction_info(void);

void update_graphics(void)
{
    uint16_t mapDrawX = game.mapPos.x * TILE_WIDTH;
    uint16_t mapDrawY = game.mapPos.y * TILE_HEIGHT;

    uint16_t playerDrawX = TILE_WIDTH * (player.pos.x - game.mapPos.x) + tilemap.x_loc;
    uint8_t playerDrawY = TILE_HEIGHT * (player.pos.y - game.mapPos.y) + tilemap.y_loc;

    gfx_Tilemap_NoClip(&tilemap, mapDrawX, mapDrawY);
    gfx_RLETSprite_NoClip(sprite_spherix, playerDrawX, playerDrawY);

    if(game.cur_msg) output_cur_message();
}

// All the sprites are on the sidebar are 16x16px
#define SPRITE_16_PX    16

// Control sidebar location and spacing
#define TEXT_SPACING    (SPRITE_16_PX * 5 / 4)
#define SIDEBAR_POS_X   (LCD_WIDTH - tilemap_draw_width_px - tilemap.y_loc - SPRITE_16_PX)
#define START_TEXT_Y    tilemap.y_loc

#define TEXT_HEIGHT 8
void output_cur_message(void)
{
    uint8_t windowHeight = LCD_HEIGHT / 12;

    gfx_SetColor(BLACK_COLOR);
    gfx_SetTextBGColor(BLACK_COLOR);
    gfx_SetTextFGColor(WHITE_COLOR);

    gfx_FillRectangle_NoClip(0, LCD_HEIGHT - windowHeight, LCD_WIDTH, windowHeight);
    gfx_PrintStringXY(game.cur_msg, SIDEBAR_POS_X, LCD_HEIGHT - windowHeight + ((windowHeight - TEXT_HEIGHT) / 2));
}

void draw_background(void)
{
    gfx_SetTextFGColor(TRANSPARENT_GRAY);
	gfx_SetTextBGColor(BLACK_COLOR);

    display_borders();

    // change index param to swap positions around
    display_key_info(0);
    display_endGem_info(2);

    // message and direction info displayed in same spot
    if(!game.cur_msg) display_direction_info();
}

static void display_borders(void)
{
    gfx_SetColor(BLACK_COLOR);
    gfx_FillRectangle_NoClip(0, 0, LCD_WIDTH, tilemap.y_loc); // top
    gfx_FillRectangle_NoClip(0, tilemap.y_loc + tilemap_draw_height_px, LCD_WIDTH, LCD_HEIGHT - tilemap.y_loc - tilemap_draw_height_px); // bottom
    gfx_FillRectangle_NoClip(0, 0, tilemap.x_loc, LCD_HEIGHT); // left
    gfx_FillRectangle_NoClip(tilemap.x_loc + tilemap_draw_width_px, 0, LCD_WIDTH - tilemap.x_loc - tilemap_draw_width_px, LCD_HEIGHT); // right
}

static void display_key_info(uint8_t index)
{
    gfx_RLETSprite_NoClip(sprite_key, SIDEBAR_POS_X, START_TEXT_Y + TEXT_SPACING * index);
	gfx_PrintUIntXY(game.numKeys, 1, SIDEBAR_POS_X, START_TEXT_Y + TEXT_SPACING * (index + 1));
}

static void display_endGem_info(uint8_t index)
{
	gfx_RLETSprite_NoClip(sprite_gem, SIDEBAR_POS_X, START_TEXT_Y + TEXT_SPACING * index);
	if (!game.hasEndGem) {
		gfx_RLETSprite_NoClip(sprite_x_mark, SIDEBAR_POS_X, START_TEXT_Y + TEXT_SPACING * (index + 1));
	}
	else {
		gfx_RLETSprite_NoClip(sprite_check, SIDEBAR_POS_X, START_TEXT_Y + TEXT_SPACING * (index + 1));
	}
}

// more "lower info" to be added later
static void display_direction_info(void)
{
    gfx_SetColor(WHITE_COLOR);
    
    const uint8_t drawY = tilemap.y_loc + tilemap_draw_height_px - SPRITE_16_PX;

    gfx_RLETSprite_NoClip(sprite_arrows[player.facing], SIDEBAR_POS_X, drawY);
}

void display_framerate(uint16_t frametime) 
{
    gfx_SetTextFGColor(TRANSPARENT_GRAY);

    const uint8_t drawY = tilemap.y_loc + tilemap_draw_height_px - SPRITE_16_PX - 3 * TEXT_SPACING / 5;

    gfx_PrintUIntXY(32768 / frametime, 2, SIDEBAR_POS_X, drawY);
}