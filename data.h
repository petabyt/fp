#pragma once

#include <stdint.h>
#include <string.h>

struct FujiLookup {
	char *key;
	uint32_t value;
};

extern struct FujiLookup fp_film_sim[];
extern struct FujiLookup fp_on_off[];
extern struct FujiLookup fp_bool[];
extern struct FujiLookup fp_grain_effect[];
extern struct FujiLookup fp_chrome_effect[];
extern struct FujiLookup fp_file_type[];
extern struct FujiLookup fp_grain_effect_size[];
extern struct FujiLookup fp_image_size[];
extern struct FujiLookup fp_image_quality[];
extern struct FujiLookup fp_exposure_bias[];
extern struct FujiLookup fp_white_balance[];
extern struct FujiLookup fp_color_temp[];
extern struct FujiLookup fp_range[];
extern struct FujiLookup fp_color_space[];
