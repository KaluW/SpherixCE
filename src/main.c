#include <graphx.h>
#include <keypadc.h>
#include <stdint.h>
#include <tice.h>

#include "defines.h"
#include "images.h"
#include "graphics.h"
#include "levels.h"
#include "player.h"
#include "tile_handlers.h"

player_t player;
game_t game;

static bool allowLoopRun(void);

void main(void)
{
    uint16_t frametime = 0;
    uint8_t fixedFPS = 30;
    bool displayFPS = true;

    gfx_Begin(gfx_8bpp);

    // set up some stuff 
    create_levels();
    extract_sprites();
    extract_tiles();

    // everything that will stay constant in the tilemap struct
    setup_tilemap_constants();

    // This will change when I incorporate multiple pack suppport/custom packs
    game.numLevels = get_num_levels();
    game.curr_level = 1;

HANDLE_LEVEL_START:
    // stuff that changes between levels
    extract_level();

    gfx_SetDrawBuffer();

    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;

    // main
    do
    {
        handle_keypad();

        // ah yes, the structurally integrous 'goto' command
        if(!allowLoopRun()) goto HANDLE_LOOP_SKIP;

        update_player();

        handle_tile_events();

        draw_background();
        update_graphics();

        if (displayFPS) display_framerate(frametime);

        gfx_SwapDraw();

HANDLE_LOOP_SKIP:
        if(fixedFPS) while(timer_1_Counter < frames(fixedFPS));

        frametime = timer_1_Counter;
        timer_1_Counter = 0;

    } while(!player.keypad.pressed_Clear && !game.hasWonLevel);

    timer_Control = TIMER1_DISABLE;
    free(tilemap.map);

    if(player.keypad.pressed_Clear) goto HANDLE_EXIT;

    if(game.curr_level < game.numLevels)
    {
        game.curr_level++;
        goto HANDLE_LEVEL_START;
    }

HANDLE_EXIT:
    gfx_End();

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

static bool allowLoopRun(void)
{
    if(os_GetCSC() && !player.keypad.pressed_2nd && game.cur_msg)
    {
        game.cur_msg = NULL;
    }

    if(player.keypad.allow_down_press) return true;
    
    return false;    
}
