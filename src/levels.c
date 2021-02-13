#include <fileioc.h>
#include <graphx.h>
#include <stdbool.h>
#include <stdint.h>

#include "defines.h"
#include "images.h"
#include "levels.h"
#include "player.h"

uint16_t tilemap_draw_width_px;
uint8_t tilemap_draw_height_px;

static void extract_level_data(tiles_t* in, uint8_t* out);
static void config_tilemap_globals(uint16_t draw_width, uint8_t draw_height);

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

#define bow boulder_on_water_tile
#define bob boulder_on_button_tile

static tiles_t level_1[12 * 9] = {
    wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal,
    wal, flr, flr, wal, flr, flr, fW1, key, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, wal, flr, flr, flr, flr, wal,
    wal, wal, wal, wal, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, ceG, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, flr, wal,
    wal, flr, flr, flr, flr, flr, flr, flr, flr, flr, enP, wal,
    wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal, wal,
};

static tiles_t level_2[13*17] = {
    wal, wal, wal, wal, wal, wal, wal, hol, hol, hol, hol, hol, hol,
    wal, key, flr, flr, flr, ceG, wal, hol, hol, hol, hol, hol, hol,
    wal, flr, flr, flr, flr, flr, wal, hol, hol, hol, hol, hol, hol,
    wal, flr, flr, flr, flr, flr, wal, hol, hol, hol, hol, hol, hol,
    wal, flr, blr, blr, blr, flr, wal, hol, hol, hol, hol, hol, hol,
    wal, blr, flr, flr, flr, blr, wal, hol, wal, wal, wal, wal, wal,
    wal, flr, blr, cBl, blr, flr, wal, wal, wal, enP, flr, wal, wal,
    wal, blr, blr, flr, blr, blr, wal, wal, wal, flr, flr, flr, wal,
    hol, wal, flr, flr, flr, wal, wal, key, h2o, h2o, flr, flr, wal,
    wal, wal, wal, flr, wal, hol, flr, flr, h2o, h2o, flr, flr, wal,
    wal, flr, flr, flr, wal, blr, flr, blr, flr, cBl, flr, flr, wal,
    wal, flr, wal, wal, wal, flr, blr, flr, blr, flr, h2o, h2o, wal,
    wal, flr, wal, key, flr, flr, flr, blr, flr, blr, h2o, h2o, wal,
    wal, flr, wal, flr, flr, flr, flr, flr, blr, flr, flr, wal, wal,
    wal, flr, wal, wal, wal, wal, cBl, flr, flr, flr, flr, wal, hol,
    wal, flr, key, flr, flr, flr, flr, wal, wal, wal, wal, wal, hol,
    wal, wal, wal, wal, wal, wal, wal, wal, hol, hol, hol, hol, hol
};

void create_levels(void)
{
    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixL", "w");

    uint8_t numLevels = 2;

    level_t levels[2] = {
        [0]= {
            .width = 12,
            .height = 9,
            .enum_map = level_1,

            .map_start.x = 0,
            .map_start.y = 0,

            .player_start.x = 1,
            .player_start.y = 1,

            .draw_width = 9,
            .draw_height = 7
        },
        [1]= {
            .width = 13,
            .height = 17,
            .enum_map = level_2,

            .map_start.x = 0,
            .map_start.y = 0,

            .player_start.x = 3,
            .player_start.y = 2,

            .draw_width = 9,
            .draw_height = 7
        }
    };

    ti_PutC(numLevels, slot);
    ti_Write(&levels[0], sizeof(level_t), 1, slot);
    ti_Write(&levels[1], sizeof(level_t), 1, slot);

    ti_CloseAll();
}

uint8_t get_num_levels(void)
{
    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixL", "r");
    
    if(!slot)
    {
        ti_CloseAll();
        handle_error("Failed to load level");
    }

    return ti_GetC(slot);

    ti_CloseAll();
}

void extract_level(void)
{
    level_t level;

    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixL", "r");
    
    if(!slot)
    {
        ti_CloseAll();
        handle_error("Failed to load level");
    }

    ti_Seek(sizeof(level_t) * (game.curr_level - 1) + 1, SEEK_SET, slot);

    ti_Read(&level, sizeof(level_t), 1, slot);

    game.enum_map = level.enum_map;

    tilemap.width = level.width;
    tilemap.height = level.height;

    tilemap.map = malloc(level.width * level.height);

    tiles_t* in = level.enum_map;
    uint8_t* out = tilemap.map;

    // Extract the level data into a tilemap
    extract_level_data(in, out);

    // starting values
    game.mapPos.x = level.map_start.x;
    game.mapPos.y = level.map_start.y;

    player.pos.x = level.player_start.x;
    player.pos.y = level.player_start.y;

    game.numKeys = 0;
    game.hasEndGem = false;
    game.hasWonLevel = false;

   config_tilemap_globals(level.draw_width, level.draw_height);
}

static void extract_level_data(tiles_t* in, uint8_t* out)
{
    for(uint8_t i = 0; i < tilemap.width * tilemap.height; i++)
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
            free(tilemap.map);
            handle_error("Invalid level data");
        }

        in++;
        out++;                     
    }
}

static void config_tilemap_globals(uint16_t draw_width, uint8_t draw_height)
{
    // various variables I use repeatedly
    tilemap.draw_width = draw_width;
    tilemap.draw_height = draw_height;

    tilemap_draw_width_px = TILE_WIDTH * draw_width;
    tilemap_draw_height_px = TILE_HEIGHT * draw_height;

    // put space between the tilemap and the border of the lcd screen
    uint8_t offset = (LCD_HEIGHT - tilemap_draw_height_px) / 2;

    tilemap.y_loc = LCD_HEIGHT - tilemap_draw_height_px - offset;
    tilemap.x_loc = LCD_WIDTH - tilemap_draw_width_px - offset;
}

void setup_tilemap_constants(void)
{
    tilemap.tiles = tileset_tiles;
    tilemap.type_width = gfx_tile_32_pixel;
    tilemap.type_height = gfx_tile_32_pixel;
    tilemap.tile_height = TILE_HEIGHT;
    tilemap.tile_width = TILE_WIDTH;

    // initialize to make some things work properly
    tilemap.height = 0;
    tilemap.width = 0;
}