#include <fileioc.h>
#include <graphx.h>
#include <stdint.h>

#include "images.h"
#include "defines.h"
#include "player.h"
#include "tile_handlers.h"

gfx_tilemap_t tilemap;
gfx_sprite_t *tileset_tiles[TILE_COUNT];

gfx_rletsprite_t* sprite_spherix;
gfx_rletsprite_t* sprite_gem;
gfx_rletsprite_t* sprite_key;
gfx_rletsprite_t* sprite_x_mark;
gfx_rletsprite_t* sprite_check;

gfx_rletsprite_t* sprite_arrows[4];

void extract_sprites(void)
{
    uint8_t slot;

    ti_CloseAll();
    slot = ti_Open("SpherixS", "r");
    if (!slot)
        handle_error("Missing Appvars");
    
    uint8_t* spr_ptr = ti_GetDataPtr(slot);
    gfx_TempSprite(spr_ptr0, 32, 32);

    sprite_spherix = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 1026;
    sprite_gem = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_key = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_x_mark = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_check = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);
    spr_ptr += 258;
    sprite_arrows[down] = gfx_ConvertMallocRLETSprite((gfx_sprite_t*)spr_ptr);

    gfx_RotateSpriteCC((gfx_sprite_t*)spr_ptr, spr_ptr0);
    sprite_arrows[right] = gfx_ConvertMallocRLETSprite(spr_ptr0);

    gfx_FlipSpriteX((gfx_sprite_t*)spr_ptr, spr_ptr0);
    sprite_arrows[up] = gfx_ConvertMallocRLETSprite(spr_ptr0);

    gfx_RotateSpriteC((gfx_sprite_t*)spr_ptr, spr_ptr0);
    sprite_arrows[left] = gfx_ConvertMallocRLETSprite(spr_ptr0);

    ti_CloseAll();
}

void extract_tiles(void)
{
    ti_CloseAll();
    uint8_t slot = ti_Open("SpherixT", "r");
    if (!slot)
        handle_error("Missing Appvars");

    uint16_t pal_size;
    uint16_t* pal_ptr;
    uint8_t* tmp_ptr;
    gfx_sprite_t** tiles = tileset_tiles;

    pal_ptr = (uint16_t*)ti_GetDataPtr(slot);
    pal_size = *pal_ptr;
    pal_ptr++;

    // set up the palette
    gfx_SetPalette(pal_ptr, pal_size, 0);
    tmp_ptr = (uint8_t*)pal_ptr;
    tmp_ptr += pal_size;

    // store tile pointers
    for (uint8_t i = 0; i < TILE_COUNT; i++)
    {
        tiles[i] = (gfx_sprite_t*)tmp_ptr;
        tmp_ptr += TILE_DATA_SIZE;
    }

    // close the open file
    ti_CloseAll();
}