#ifndef LEVELS_H
#define LEVELS_H

#include <stdint.h>

#include "defines.h"
#include "player.h"

void create_levels(void);
void extract_level(void);
void setup_tilemap(void);

typedef struct Level
{
    uint8_t width;
    uint8_t height;
    tiles_t* enum_map;

    pos_t player_start;
    pos_t map_start;
} level_t;

#endif