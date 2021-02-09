#include <stdint.h>
#include <graphx.h>
#include <tice.h>

#include "defines.h"
#include "images.h"
#include "levels.h"
#include "player.h"
#include "tile_handlers.h"

void display_fps(uint16_t frametime);
void setup_tilemap(gfx_tilemap_t* tilemap, gfx_sprite_t** tileset_tiles);

void main(void)
{
    uint16_t frametime = 0;

    gfx_Begin();

    player_t player;
    game_t game;
    gfx_rletsprite_t* sprites[SPRITE_COUNT];
    gfx_sprite_t* tileset_tiles[TILE_COUNT];

    // set up some stuff 
    create_levels();
    extract_sprites(sprites);
    extract_tiles(tileset_tiles);

    // everything that will stay constant in the tilemap struct
    setup_tilemap(&game.tile_map, tileset_tiles);

    // stuff that changes between levels
    extract_level(&player, &game);

    gfx_SetDrawBuffer();

    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;

    // main
    do
    {
        handle_keypad(&player.keypad);
        update_player(&game, &player);

        handle_tile_events(player, &game);

        draw_background(game, sprites);
        update_graphics(player, game, sprites);

        display_fps(frametime);

        gfx_SwapDraw();

        if(FIXFPS) while(timer_1_Counter < FIXED_FPS);

        frametime = timer_1_Counter;
        timer_1_Counter = 0;

    } while(!player.keypad.pressed_Clear);

    free(game.tile_map.map);

    gfx_End();
}

void display_fps(uint16_t frametime)
{
    gfx_SetTextBGColor(BLACK_COLOR);
    gfx_SetTextFGColor(WHITE_COLOR);

    gfx_SetTextXY(1, 1);
    gfx_PrintUInt(32768 / frametime, 2);
}

// function prototype in defines.h
void handle_error(const char* msg)
{
    gfx_End();
    os_ClrHomeFull();

    os_SetCursorPos(0, 0);
    os_PutStrFull("Error:");

    os_SetCursorPos(1, 0);
    os_PutStrFull(msg);

    while (!os_GetCSC());

    exit(0);
}

void setup_tilemap(gfx_tilemap_t* tilemap, gfx_sprite_t** tileset_tiles)
{
    tilemap->tiles = tileset_tiles;
    tilemap->type_width = gfx_tile_32_pixel;
    tilemap->type_height = gfx_tile_32_pixel;
    tilemap->tile_height = TILE_HEIGHT;
    tilemap->tile_width = TILE_WIDTH;
    tilemap->draw_height = TILEMAP_DRAW_HEIGHT;
    tilemap->draw_width = TILEMAP_DRAW_WIDTH;
    tilemap->y_loc = TILEMAP_START_DRAW_Y;
    tilemap->x_loc = TILEMAP_START_DRAW_X;

    // initialize to make some things work properly
    tilemap->height = 0;
    tilemap->width = 0;
}
