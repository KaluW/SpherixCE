#include <graphx.h>

#include "defines.h"
#include "player.h"
#include "tile_handlers.h"

void handle_keypad(keypad_t* keypad)
{
    kb_Scan();

    keypad->dir_press = kb_Data[7]; // directions offset - up, down, left, right

    keypad->pressed_2nd = (kb_Data[1] & kb_2nd);
    keypad->pressed_Alpha = (kb_Data[2] & kb_Alpha);
    keypad->pressed_Clear = (kb_Data[6] & kb_Clear); // exit
}

void update_player(game_t* game, player_t* player)
{
    uint8_t* map_x = &game->mapPos.x;
    uint8_t* map_y = &game->mapPos.y;

    uint8_t right_bound = game->tile_map.width;
    uint8_t bottom_bound = game->tile_map.height;

    uint8_t screen_center_x = TILEMAP_DRAW_WIDTH / 2;
    uint8_t screen_center_y = TILEMAP_DRAW_HEIGHT / 2;

    uint8_t* player_x = &player->pos.x;
    uint8_t* player_y = &player->pos.y;

    kb_key_t direction = player->keypad.dir_press;

    switch(direction)
    {
        case kb_Left:
            player->facing = left;
            if (!isLegalMove(player, game)) return;

            (*player_x)--;

            // scroll the map
            if (*map_x && *player_x - *map_x <= screen_center_x)
            {
                (*map_x)--;
            }

            break;
        
        case kb_Right:
            player->facing = right;
            if (!isLegalMove(player, game)) return;

            (*player_x)++;

            if (*map_x + TILEMAP_DRAW_WIDTH < right_bound && *player_x - *map_x >= screen_center_x)
            {
                (*map_x)++;
            }

            break;

        case kb_Up:
            player->facing = up;
            if (!isLegalMove(player, game)) return;

            (*player_y)--;

            if (*map_y && *player_y - *map_y <= screen_center_y)
            {
                (*map_y)--;
            }

            break;

        case kb_Down:
            player->facing = down;
            if (!isLegalMove(player, game)) return;

            (*player_y)++;

            if (*map_y + TILEMAP_DRAW_HEIGHT < bottom_bound && *player_y - *map_y >= screen_center_y)
            {
                (*map_y)++;
            }

            break;

        default:
            break;
    }
}

bool isLegalMove(player_t* player, game_t* game)
{
    uint16_t test_x = _test_pos_x(player->pos.x, player->facing);
    uint8_t test_y = _test_pos_y(player->pos.y, player->facing);

    tiles_t test_tile = game->enum_map[test_y * game->tile_map.width + test_x];

    player->isPushingBoulder = (test_tile == boulder_tile) ? true : false;

    return (test_tile == floor_tile);
}