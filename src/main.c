#include <graphx.h>
#include <stdint.h>
#include <tice.h>

#include "defines.h"
#include "images.h"
#include "levels.h"
#include "player.h"
#include "tile_handlers.h"

player_t player;
game_t game;

void display_fps(uint16_t frametime);

void main(void)
{
    uint16_t frametime = 0;

    gfx_Begin();

    // set up some stuff 
    create_levels();
    extract_sprites();
    extract_tiles();

    // everything that will stay constant in the tilemap struct
    setup_tilemap();

    // stuff that changes between levels
    extract_level();

    gfx_SetDrawBuffer();

    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;

    // main
    do
    {
        handle_keypad();
        update_player();

        handle_tile_events();

        draw_background();
        update_graphics();

        display_fps(frametime);

        gfx_SwapDraw();

        if(FIXFPS) while(timer_1_Counter < fixed_fps(30));

        frametime = timer_1_Counter;
        timer_1_Counter = 0;

    } while(!player.keypad.pressed_Clear);

    free(tilemap.map);

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
