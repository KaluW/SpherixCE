#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>
#include <stdint.h>
#include <tice.h>
#include <graphx.h>

/**
 * Totally necessary explanations to excuse my poor code structuring
 * 
 * The game contains two maps: the enumerated map and the tilemap.
 * The enumerated map includes data that is otherwise impossible to represent in the actual tilemap array.
 * E.g. the presence of fake walls, boulders on sticky buttons, and activated switches 
 * The tilemap of course is just an array of sprite pointer indices.
 * 
 * Note to unfortunate reader: the #define'd tileset indices begin with "TILE_" while the similar enum either 
 * begin with "tiles_", or end with "_tile" or with "_sptile" depending on its function.
 */

// In main
void handle_error(const char* msg);

#define FIXED_FPS 32768 / 10
#define FIXFPS true

// Color defines
#define TRANSPARENT_GRAY 0
#define BLACK_COLOR 1
#define WHITE_COLOR 2

// Tilemap defines
#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define TILE_DATA_SIZE TILE_WIDTH * TILE_HEIGHT + 2
#define TILEMAP_DRAW_WIDTH 9
#define TILEMAP_DRAW_HEIGHT	7
#define TILEMAP_START_DRAW_X (LCD_WIDTH - (TILE_WIDTH * TILEMAP_DRAW_WIDTH)) * 3 / 4
#define TILEMAP_START_DRAW_Y (LCD_HEIGHT - (TILE_HEIGHT * TILEMAP_DRAW_HEIGHT)) / 2

#define TILE_COUNT 12
#define SPRITE_COUNT 5

// Sprite defines
#define SPRITE_SPHERIX  0
#define SPRITE_GEM      1
#define SPRITE_KEY      2
#define SPRITE_X_MARK   3
#define SPRITE_CHECK    4

// Tileset defines
#define TILE_FLOOR 				0
#define TILE_WALL 				1
#define TILE_HOLE				2
#define TILE_KEY				3
#define TILE_ENDPORTAL			4
#define TILE_WATER				5
#define TILE_ENDGEM				6
#define TILE_BOULDER			7
#define TILE_STICKYBUTTON		8
#define TILE_UP_LADDER			9
#define TILE_DOWN_LADDER		10
#define TILE_CHEST				11

/**
 * "tiles_": groups share same tile sprite, but are enum'd so as to manipulate them individually
 * 
 * "_tile": the 'normal' tile sprites - no tile groups
 * 
 * "_sptile": Represent weird tiles. E.g. boulder on water
 */
typedef enum Tiles
{
    tiles_fake_wall_1,
    tiles_fake_wall_2,
    tiles_fake_wall_3,
    tiles_fake_wall_4,
    tiles_fake_wall_5,

    tiles_button_1,
    tiles_button_2,
    tiles_button_3,
    tiles_button_4,
    tiles_button_5,

    tiles_up_ladder_1,
    tiles_up_ladder_2,
    tiles_up_ladder_3,
    tiles_up_ladder_4,
    tiles_up_ladder_5,

    tiles_down_ladder_1,
    tiles_down_ladder_2,
    tiles_down_ladder_3,
    tiles_down_ladder_4,
    tiles_down_ladder_5,

    tiles_chest_endGem,
    tiles_chest_boulder,

    floor_tile,
    wall_tile,
    hole_tile,
    key_tile,
    endPortal_tile,
    water_tile,
    endGem_tile,
    boulder_tile
} tiles_t;

// A bunch of structs ↓↓↓

typedef enum Directions
{
    none,
    up,
    down,
    left,
    right
} directions_t;

typedef struct Map
{
    uint8_t width, height;
    tiles_t* enum_map;
} map_t;

typedef struct Pos
{
    uint8_t x;
    uint8_t y;
} pos_t;

typedef struct Level
{
    map_t map;

    pos_t player_start;
    pos_t map_start;
} level_t;

typedef struct Game
{
    uint8_t curr_level;

    tiles_t* enum_map;
    gfx_tilemap_t tile_map;

    pos_t mapPos;
    
    uint8_t numKeys;
    bool hasEndGem;
} game_t;

#endif