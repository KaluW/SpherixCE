#include <stdbool.h>
#include <graphx.h>
#include <tice.h>

#include "defines.h"
#include "images.h"
#include "player.h"
#include "tile_handlers.h"

static bool isLegalMove(void);

void handle_keypad(void)
{
    keypad_t* keypad = &player.keypad;

    keypad->prev_press = keypad->dir_press;

    kb_Scan();

    keypad->dir_press = kb_Data[7];

    keypad->allow_down_press = (!keypad->prev_press) ? true : false;

    keypad->pressed_down = (keypad->dir_press) ? true : false;
    
    keypad->pressed_2nd = (kb_Data[1] & kb_2nd);
    keypad->pressed_Alpha = (kb_Data[2] & kb_Alpha);
    
    keypad->pressed_Clear = (kb_Data[6] & kb_Clear);
}

void update_player(void)
{
    uint8_t* map_x = &game.mapPos.x;
    uint8_t* map_y = &game.mapPos.y;

    uint8_t right_bound = tilemap.width;
    uint8_t bottom_bound = tilemap.height;

    uint8_t screen_center_x = tilemap.draw_width / 2;
    uint8_t screen_center_y = tilemap.draw_height / 2;

    uint8_t* player_x = &player.pos.x;
    uint8_t* player_y = &player.pos.y;

    kb_key_t direction = player.keypad.dir_press;

    switch(direction)
    {
        case kb_Left:
            player.facing = left;
            if (!isLegalMove()) return;

            (*player_x)--;

            // scroll the map
            if (*map_x && *player_x - *map_x < screen_center_x)
            {
                (*map_x)--;
            }

            break;
        
        case kb_Right:
            player.facing = right;
            if (!isLegalMove()) return;

            (*player_x)++;

            if (*map_x + tilemap.draw_width < right_bound && *player_x - *map_x > screen_center_x)
            {
                (*map_x)++;
            }

            break;

        case kb_Up:
            player.facing = up;
            if (!isLegalMove()) return;

            (*player_y)--;

            if (*map_y && *player_y - *map_y < screen_center_y)
            {
                (*map_y)--;
            }

            break;

        case kb_Down:
            player.facing = down;
            if (!isLegalMove()) return;

            (*player_y)++;

            if (*map_y + tilemap.draw_height < bottom_bound && *player_y - *map_y > screen_center_y)
            {
                (*map_y)++;
            }

            break;

        default:
            break;
    }
}

static bool isLegalMove(void)
{
    uint16_t test_x = test_pos_x(player.pos.x);
    uint8_t test_y = test_pos_y(player.pos.y);

    tiles_t test_tile = game.enum_map[test_y * tilemap.width + test_x];

    player.isPushingBoulder = (test_tile == boulder_tile) ? true : false;

    return (test_tile == floor_tile);
}