#ifndef TILE_HANDLERS_H
#define TILE_HANDLERS_H

#include <stdint.h>
#include <stdbool.h>

#include "player.h"

uint8_t _test_pos_x(uint8_t x, directions_t dir);
uint8_t _test_pos_y(uint8_t y, directions_t dir);

void handle_tile_events(player_t player, game_t* game);

void handle_boulder(player_t player, game_t* game);
void handle_chest(player_t player, game_t* game);
void handle_endGem(game_t* game);
void handle_key(game_t* game);

#endif