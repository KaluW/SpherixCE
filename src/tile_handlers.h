#ifndef TILE_HANDLERS_H
#define TILE_HANDLERS_H

#include <stdbool.h>
#include <stdint.h>

#include "player.h"

// Wutyu gonna do 'bout it?
typedef struct {
    pos_t curr;
    uint16_t index;
} this_t;

uint8_t _test_pos_x(uint8_t x);
uint8_t _test_pos_y(uint8_t y);

void handle_tile_events(void);

void handle_boulder(const this_t* this);
void handle_chest(const this_t* this);
void handle_endGem(const this_t* this);
void handle_key(const this_t* this);
void handle_endPortal(void);

#endif