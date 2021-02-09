#include <graphx.h>
#include <stdint.h>

#include "defines.h"
#include "images.h"
#include "player.h"
#include "tile_handlers.h"

uint8_t _test_pos_x(uint8_t x)
{
    if (player.facing == left) return x - 1;
    if (player.facing == right) return x + 1;

    return x;
}

uint8_t _test_pos_y(uint8_t y)
{
    if (player.facing == up) return y - 1;
    if (player.facing == down) return y + 1;

    return y;
}

void handle_tile_events(void)
{
    uint8_t x_pos = _test_pos_x(player.pos.x);
    uint8_t y_pos = _test_pos_y(player.pos.y);

    uint16_t index = y_pos * tilemap.width + x_pos;

    uint8_t test_tile = tilemap.map[index];
    
    switch(test_tile)
    {
        case TILE_CHEST:
            handle_chest();
            break;

        case TILE_BOULDER:
            handle_boulder();
            break;

        default:
            break;
    }
}

void handle_boulder(void)
{
    // needed code logic. Otherwise I have to move player within the tile_handler module.
    if(!player.isPushingBoulder) return;

    // current boulder pos
    uint8_t curr_x_pos = _test_pos_x(player.pos.x);
    uint8_t curr_y_pos = _test_pos_y(player.pos.y);

    // test boulder pos
    uint8_t test_x_pos = _test_pos_x(curr_x_pos);
    uint8_t test_y_pos = _test_pos_y(curr_y_pos);

    // Readability :)
    uint16_t index = curr_y_pos * tilemap.width + curr_x_pos;
    uint16_t test_index = test_y_pos * tilemap.width + test_x_pos;
    tiles_t* curr_tile = &game.enum_map[index];
    tiles_t* test_tile = &game.enum_map[test_index];
    
    switch(*test_tile)
    {
        case floor_tile:
            // move boulder to new position
            gfx_SetTileMapped(&tilemap, test_x_pos, test_y_pos, TILE_BOULDER);
            *test_tile  = boulder_tile;
            
        case hole_tile:
            // replace old tile with floor
            gfx_SetTileMapped(&tilemap, curr_x_pos, curr_y_pos, TILE_FLOOR);
            *curr_tile = floor_tile;

            break;

        default:
            break;
    }
}

void handle_chest(void)
{
    // if action wasn't triggered or key isn't owned, return
    if (!player.keypad.pressed_2nd || !game.numKeys) return;

    uint8_t x_pos = _test_pos_x(player.pos.x);
    uint8_t y_pos = _test_pos_y(player.pos.y);

    uint16_t index = y_pos * tilemap.width + x_pos;

    tiles_t* tile = &game.enum_map[index];

    if(*tile == tiles_chest_boulder)
    {
        gfx_SetTileMapped(&tilemap, x_pos, y_pos, TILE_BOULDER);
        *tile = boulder_tile;
        
        game.numKeys--;

        return;
    }
}

void handle_endGem(void)
{

}

void handle_key(void)
{

}