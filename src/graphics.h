#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

void update_graphics(void);
void draw_background();
void output_cur_message(void);
void display_framerate(uint16_t frametime);

#endif