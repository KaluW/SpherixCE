#ifndef TILE_HANDLERS_H
#define TILE_HANDLERS_H

#include <stdbool.h>
#include <stdint.h>

#include "player.h"

uint8_t _test_pos_x(uint8_t x);
uint8_t _test_pos_y(uint8_t y);

void handle_tile_events(void);

void handle_boulder(void);
void handle_chest(void);
void handle_endGem(void);
void handle_key(void);

#endif