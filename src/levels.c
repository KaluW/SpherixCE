#include <stdbool.h>
#include <stdint.h>
#include <fileioc.h>
#include <graphx.h>

#include "defines.h"
#include "levels.h"
#include "player.h"

// These are short-hand names are so I can understand the level maps I create visually

#define fW1 tiles_fake_wall_1
#define fW2 tiles_fake_wall_2
#define fW3 tiles_fake_wall_3
#define fW4 tiles_fake_wall_4
#define fW5 tiles_fake_wall_5
#define sB1 tiles_button_1
#define sB2 tlies_button_2
#define sB3 tiles_button_3
#define sB4 tiles_button_4
#define sB5 tiles_button_5
#define uL1 tiles_up_ladder_1
#define uL2 tiles_up_ladder_2
#define uL3 tiles_up_ladder_3
#define uL4 tiles_up_ladder_4
#define uL5 tiles_up_ladder_5
#define dL1 tiles_down_ladder_1
#define dL2 tiles_down_ladder_2
#define dL3 tiles_down_ladder_3
#define dL4 tiles_down_ladder_4
#define dL5 tiles_down_ladder_5
#define ceG tiles_chest_endGem
#define cBl tiles_chest_boulder

#define flr floor_tile
#define wal wall_tile
#define hol hole_tile
#define key key_tile
#define enP endPortal_tile
#define h2o water_tile
#define enG endGem_tile
#define blr boulder_tile

// these globals don't count :P

tiles_t enum_map_1[12 * 9] = {
    wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal,
    wal, flr, flr, wal, flr, flr, fW1, enG, h2o, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, wal, h2o, h2o, flr, flr, wal,
    wal, wal, wal, wal, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, cBl, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, enP, wal,
    wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal,
};

void create_levels(void)
{
    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixL", "w");

    // currently only one level. level_t array should work with multiple levels
    level_t levels = {
        .map.width = 12,
        .map.height = 9,
        .map.enum_map = enum_map_1,

        .map_start.x = 0,
        .map_start.y = 0,

        .player_start.x = 1,
        .player_start.y = 1
    };

    ti_Write(&levels, sizeof(level_t), 1, slot);

    ti_CloseAll();
}

void extract_level(player_t* player, game_t* game)
{
    level_t level;

    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixL", "r");
    
    if(!slot)
    {
        ti_CloseAll();
        handle_error("Failed to load level");
    }

    ti_Read(&level, sizeof(level_t), 1, slot);

    game->enum_map = level.map.enum_map;

    game->tile_map.width = level.map.width;
    game->tile_map.height = level.map.height;

    game->tile_map.map = malloc(level.map.width * level.map.height);

    tiles_t* in = level.map.enum_map;
    uint8_t* out = game->tile_map.map;

    // Extract the level data into a tilemap
    for(uint8_t i = 0; i < level.map.width * level.map.height; i++)
    {
            if (*in == floor_tile)          { *out = TILE_FLOOR;        } else
            if (*in == wall_tile)           { *out = TILE_WALL;         } else
            if (*in == hole_tile)           { *out = TILE_HOLE;         } else
            if (*in == key_tile)            { *out = TILE_KEY;          } else
            if (*in == endPortal_tile)      { *out = TILE_ENDPORTAL;    } else
            if (*in == water_tile)          { *out = TILE_WATER;        } else
            if (*in == endGem_tile)         { *out = TILE_ENDGEM;       } else
            if (*in == boulder_tile)        { *out = TILE_BOULDER;      } else
            if (*in >= tiles_fake_wall_1 && *in <= tiles_fake_wall_5) // fake walls
            {
                *out = TILE_WALL;
            } else 
            if (*in >= tiles_button_1 && *in <= tiles_button_5) // sticky buttons
            {
                *out = TILE_STICKYBUTTON;
            } else
            if (*in >= tiles_up_ladder_1 && *in <= tiles_up_ladder_5) // up ladders
            {
                *out = TILE_UP_LADDER;
            } else
            if (*in >= tiles_down_ladder_1 && *in <= tiles_down_ladder_5) // down ladders
            {
                *out = TILE_DOWN_LADDER;
            } else 
            if (*in == tiles_chest_boulder || *in == tiles_chest_endGem) // chests
            {
                *out = TILE_CHEST;
            } else
            {
                free(game->tile_map.map);
                handle_error("Invalid level data");
            }

           in++;
           out++;                     
    }

    // starting values
    game->mapPos.x = level.map_start.x;
    game->mapPos.y = level.map_start.y;

    player->pos.x = level.player_start.x;
    player->pos.y = level.player_start.y;

    // these are constant every level
    game->numKeys = 1;
    game->hasEndGem = false;
}