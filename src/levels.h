#ifndef LEVELS_H
#define LEVELS_H

#include <stdint.h>

#include "defines.h"
#include "player.h"

uint8_t get_num_levels(void);
void create_levels(void);
void extract_level(void);
void setup_tilemap_constants(void);

typedef struct Level
{
    const uint8_t width;
    const uint8_t height;
    tiles_t* enum_map;

    const pos_t player_start;
    const pos_t map_start;

    uint8_t draw_width;
    uint8_t draw_height;
} level_t;

#endif