#include "defines.h"
#include "tile_handlers.h"
#include "player.h"

#include <stdint.h>
#include <graphx.h>

uint8_t _test_pos_x(uint8_t x, directions_t dir)
{
    if (dir == left) return x - 1;
    if (dir == right) return x + 1;

    return x;
}

uint8_t _test_pos_y(uint8_t y, directions_t dir)
{
    if (dir == up) return y - 1;
    if (dir == down) return y + 1;

    return y;
}

void handle_tile_events(player_t player, game_t* game)
{
    uint8_t x_pos = _test_pos_x(player.pos.x, player.facing);
    uint8_t y_pos = _test_pos_y(player.pos.y, player.facing);

    uint16_t index = y_pos * game->tile_map.width + x_pos;

    uint8_t test_tile = game->tile_map.map[index];
    
    switch(test_tile)
    {
        case TILE_CHEST:
            handle_chest(player, game);
            break;

        case TILE_BOULDER:
            handle_boulder(player, game);
            break;

        default:
            break;
    }
}

void handle_boulder(player_t player, game_t* game)
{
    // needed code logic. Otherwise I have to move player within the tile_handler module.
    if(!player.isPushingBoulder) return;

    // current boulder pos
    uint8_t curr_x_pos = _test_pos_x(player.pos.x, player.facing);
    uint8_t curr_y_pos = _test_pos_y(player.pos.y, player.facing);

    uint8_t test_x_pos = _test_pos_x(curr_x_pos, player.facing);
    uint8_t test_y_pos = _test_pos_y(curr_y_pos, player.facing);

    uint16_t index = curr_y_pos * game->tile_map.width + curr_x_pos;
    uint16_t test_index = test_y_pos * game->tile_map.width + test_x_pos;

    tiles_t* curr_tile = &game->enum_map[index];
    tiles_t* test_tile = &game->enum_map[test_index];
    
    if(*test_tile == floor_tile)
    {
        // move boulder to new position
        gfx_SetTileMapped(&game->tile_map, test_x_pos, test_y_pos, TILE_BOULDER);
        *test_tile  = boulder_tile;

        // replace old tile with floor
        gfx_SetTileMapped(&game->tile_map, curr_x_pos, curr_y_pos, TILE_FLOOR);
        *curr_tile = floor_tile;
    }
}

void handle_chest(player_t player, game_t* game)
{
    // if action wasn't triggered or key isn't owned, return
    if (!player.keypad.pressed_2nd || !game->numKeys) return;

    uint8_t x_pos = _test_pos_x(player.pos.x, player.facing);
    uint8_t y_pos = _test_pos_y(player.pos.y, player.facing);

    uint16_t index = y_pos * game->tile_map.width + x_pos;

    tiles_t* tile = &game->enum_map[index];

    if(*tile == tiles_chest_boulder)
    {
        gfx_SetTileMapped(&game->tile_map, x_pos, y_pos, TILE_BOULDER);
		*tile = boulder_tile;
		
        game->numKeys--;

		return;
    }
}

void handle_endGem(game_t* game)
{

}

void handle_key(game_t* game)
{

}