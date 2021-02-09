#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

void update_graphics(void);
void draw_background(uint16_t frametime);

void _display_key_info(uint8_t drawX);
void _display_endGem_info(uint8_t drawX);
void _display_lower(uint8_t drawX, uint16_t frametime);

#endif