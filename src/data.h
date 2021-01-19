#ifndef DATA_H
#define DATA_H

void create_tilemap(void);

// I know you're supposed to give meaningful names even to enumerations.
// However short names keeps indenting in data_map (in data.c) under sane proportions.
// underscore to differentiate sprite and enum

// button # corresponds to fake wall #
// up_ladder # corresponds to down ladder #
typedef enum tiles
{
	// special tiles - multiple functions for single tile sprite
	fWall_1, fWall_2, fWall_3, fWall_4, fWall_5, // fake walls
	button_1, button_2, button_3, button_4, button_5, // buttons -- what else?
	chest_g, chest_k, chest_b, // gem, key, boulder respectively
	up_lad_1, up_lad_2, up_lad_3, up_lad_4, up_lad_5, // up ladder
	dn_lad_1, dn_lad_2, dn_lad_3, dn_lad_4, dn_lad_5, // down ladder

	// normal tiles - one function = one tile sprite
	floor, wall, hole, _key, end, water, _gem, boulder
} tiles_t;

extern unsigned char level_map[];
extern tiles_t data_map[];

#endif