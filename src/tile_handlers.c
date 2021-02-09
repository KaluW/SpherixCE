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
    // yah sue me
    this_t this;

    this.curr.x = _test_pos_x(player.pos.x);
    this.curr.y = _test_pos_y(player.pos.y);

    this.index = this.curr.y * tilemap.width + this.curr.x;

    uint8_t test_tile = tilemap.map[this.index];
    
    switch(test_tile)
    {
        case TILE_CHEST:
            handle_chest(&this);
            break;

        case TILE_BOULDER:
            handle_boulder(&this);
            break;

        case TILE_ENDGEM:
            handle_endGem(&this);
            break;

        case TILE_KEY:
            handle_key(&this);

        case TILE_ENDPORTAL:
            handle_endPortal();

        default:
            break;
    }
}

void handle_boulder(const this_t* this)
{
    // needed code logic
    if(!player.isPushingBoulder) return;

    // test tile boulder is moving to
    uint8_t test_x = _test_pos_x(this->curr.x);
    uint8_t test_y = _test_pos_y(this->curr.y);

    uint16_t test_index = test_y * tilemap.width + test_x;

    tiles_t* curr_tile = &game.enum_map[this->index];
    tiles_t* test_tile = &game.enum_map[test_index];
    
    switch(*test_tile)
    {
        case floor_tile:
            // move boulder to new position
            gfx_SetTileMapped(&tilemap, test_x, test_y, TILE_BOULDER);
            *test_tile  = boulder_tile;
            
        case hole_tile:
            // replace old tile with floor
            gfx_SetTileMapped(&tilemap, this->curr.x, this->curr.y, TILE_FLOOR);
            *curr_tile = floor_tile;

            break;

        default:
            break;
    }
}

void handle_chest(const this_t* this)
{
    // if action wasn't triggered or key isn't owned, return
    if (!player.keypad.pressed_2nd || !game.numKeys) return;

    tiles_t* tile = &game.enum_map[this->index];

    switch(*tile)
    {
        case tiles_chest_boulder:
            gfx_SetTileMapped(&tilemap, this->curr.x, this->curr.y, TILE_BOULDER);
            *tile = boulder_tile;
            
            game.numKeys--;

            break;

        case tiles_chest_endGem:
            gfx_SetTileMapped(&tilemap, this->curr.x, this->curr.y, TILE_ENDGEM);
            *tile = endGem_tile;
            break;

        default:
            handle_error("Corrupt level data");   
    }
 
}

void handle_endGem(const this_t* this)
{
    // if action wasn't triggered, return
    if (!player.keypad.pressed_2nd) return;

    gfx_SetTileMapped(&tilemap, this->curr.x, this->curr.y, TILE_FLOOR);
    game.enum_map[this->index] = floor_tile;

    game.hasEndGem = true;
}

void handle_key(const this_t* this)
{
    // if action wasn't triggered, return
    if (!player.keypad.pressed_2nd) return;

    gfx_SetTileMapped(&tilemap, this->curr.x, this->curr.y, TILE_FLOOR);
    game.enum_map[this->index] = floor_tile;

    game.numKeys++;
}

void handle_endPortal(void)
{
    if (game.hasEndGem && player.keypad.pressed_2nd)
    {
        handle_error("You Won!");
    }
}
