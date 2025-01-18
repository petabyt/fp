// Copyright 2025 Daniel C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "fp.h"
#include "data.h"

struct FujiLookup fp_film_sim[] = {
	{"Provia", FP_Provia},
	{"Velvia", FP_Velvia},
	{"Astia", FP_Astia},
	{"Classic", FP_ClassicChrome},
//	{"ClassicNEGA", -1},
	{"NEGAStd", FP_ProNegStd},
	{"NEGAhi", FP_PRONegHi},
	{"AcrosR", FP_AcrosR},
	{"AcrosG", FP_AcrosG},
	{"AcrosYe", FP_AcrosYe},
	{"Acros", FP_AcrosSTD},
	{"Eterna", FP_Eterna},
//	{"BleachBypass", -1},
	{"BW", FP_Monochrome},
	{"BYe", FP_MonochromeYe},
	{"BR", FP_MonochromeR},
	{"BG", FP_MonochromeG},
	{"Sepia", FP_Sepia},
	{0, 0},
};
struct FujiLookup fp_on_off[] = {
	{"ON", FP_ON},
	{"OFF", FP_OFF},
	{0, 0},
};
struct FujiLookup fp_bool[] = {
	{"TRUE", FP_TRUE},
	{"FALSE", FP_FALSE},
	{0, 0},
};
struct FujiLookup fp_grain_effect[] = {
	{"OFF", FP_GRAIN_OFF},
	{"WEAK", FP_GRAIN_WEAK},
	{"STRONG", FP_GRAIN_STRONG},
	{0, 0},
};
struct FujiLookup fp_chrome_effect[] = {
	{"OFF", FP_CHROME_OFF},
	{"WEAK", FP_CHROME_WEAK},
	{"STRONG", FP_CHROME_STRONG},
	{0, 0},
};
struct FujiLookup fp_file_type[] = {
	{"JPG", FP_JPG},
	{0, 0},
};
struct FujiLookup fp_grain_effect_size[] = {
	{"SMALL", FP_GRAIN_SIZE_SMALL},
	{0, 0},
};
struct FujiLookup fp_image_size[] = {
	{"L3x2", FP_L3x2},
	{0, 0},
};
struct FujiLookup fp_image_quality[] = {
	{"Fine", FP_FINE},
	{0, 0},
};
struct FujiLookup fp_exposure_bias[] = {
	{"0", 0}, // ???
//	{"P1P00", -1}, // +1/1
	{"P0P67", 1}, // +2/3
	{"P0P33", 2}, // +1/3
//	{"P0P00", 0}, // 0
//	{"M0P33", -1} // -1/3
//	{"M0P67", -1} // -2/3
//	{"M1P00", -1} // -1/1
	{0, 0},
};
struct FujiLookup fp_white_balance[] = {
	{"AsShot", FP_WB_AsShot},
	{"INVALID", 1},
	{"Auto", FP_WB_Auto},
	{"Temperature", FP_WB_Temperature},
	{"Daylight", FP_WB_Daylight},
	{"FLight1", 123}, // ???
	{0, 0},
};
struct FujiLookup fp_color_temp[] = {
	{"0K", 0},
	{"3200K", 3200},
	{"5900K", 5900},
	{"8300K", 8300},
	{"10000K", 10000},
	{0, 0},
};
struct FujiLookup fp_range[] = {
	{"4", FP_PLUS_4},
	{"3", FP_PLUS_3},
	{"2", FP_PLUS_2},
	{"1", FP_PLUS_1},
	{"0", FP_ZERO},
	{"-1", FP_MIN_1},
	{"-2", FP_MIN_2},
	{"-3", FP_MIN_3},
	{"-4", FP_MIN_4},
	{0, 0},
};
struct FujiLookup fp_color_space[] = {
	{"sRGB", 1},
	// TODO
	{0, 0},
};

inline static int read_u8(const void *buf, uint8_t *out) {
	const uint8_t *b = buf;
	*out = b[0];
	return 1;
}
inline static int read_u16(const void *buf, uint16_t *out) {
	const uint8_t *b = buf;
	*out = (uint16_t)b[0] | ((uint16_t)b[1] << 8);
	return 2;
}
inline static int read_u32(const void *buf, uint32_t *out) {
	const uint8_t *b = buf;
	*out = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
	return 4;
}

int validate_prop(struct FPContext *ctx, uint32_t value, struct FujiLookup *tbl) {
	// TODO
	return 0;
}

static int parse_prop(struct FPContext *ctx, int idx, uint32_t value) {
	switch (idx) {
	case 0:
		//fp1->prop0 = validate_prop(ctx, value, &list);
		return 0;
	case 1:
		//fp1->prop1 = validate_prop(ctx, value, &list);
		return 0;
	case 2:
		//fp1->prop2 = validate_prop(ctx, value, &list);
		return 0;
	case 3:
		ctx->fp->ImageSize = validate_prop(ctx, value, fp_image_size);
		return 0;
	case 4:
		ctx->fp->ImageQuality = validate_prop(ctx, value, fp_image_quality);
		return 0;
	case 5:
		//fp1->prop5 = validate_prop(ctx, value, &list);
		return 0;
	case 6:
		//fp1->prop6 = validate_prop(ctx, value, &list);
		return 0;
	case 7:
		//fp1->prop7 = validate_prop(ctx, value, &list);
		return 0;
	case 8:
		ctx->fp->FilmSimulation = validate_prop(ctx, value, fp_film_sim);
		return 0;
	case 9:
		ctx->fp->GrainEffect = validate_prop(ctx, value, fp_grain_effect);
		return 0;
	case 10:
		//fp1->prop10 = validate_prop(ctx, value, &list);
		return 0;
	case 11:
		//fp1->WBShootCond = validate_prop(ctx, value, &list);
		return 0;
	case 12:
		ctx->fp->WhiteBalance = validate_prop(ctx, value, fp_white_balance);
		return 0;
	case 13:
		//fp1->WBShiftR = validate_prop(ctx, value, &list);
		return 0;
	case 14:
		//fp1->WBShiftB = validate_prop(ctx, value, &list);
		return 0;
	case 15:
		//fp1->WBColorTemp = validate_prop(ctx, value, &list);
		return 0;
	case 16:
		//fp1->HighlightTone = validate_prop(ctx, value, &list);
		return 0;
	case 17:
		//fp1->prop17 = validate_prop(ctx, value, &list);
		return 0;
	case 18:
		//fp1->prop18 = validate_prop(ctx, value, &list);
		return 0;
	case 19:
		//fp1->Sharpness = validate_prop(ctx, value, &list);
		return 0;
	case 20:
		//fp1->prop20 = validate_prop(ctx, value, &list);
		return 0;
	case 21:
		//fp1->prop21 = validate_prop(ctx, value, &list);
		return 0;
	case 22:
		ctx->fp->ColorSpace = validate_prop(ctx, value, fp_color_space);
		return 0;
	default:
		return -1;
	}
}

int fp_parse_raw(const uint8_t *bin, int len, struct FujiFP1 *fp1) {
	if (len < 0x200) return -1;

	const struct FujiBinaryProfile *profile = (const struct FujiBinaryProfile *)bin;

	uint16_t n_props;
	read_u16(&profile->n_props, &n_props);

	int expected_length = ((int)n_props * 4) + 0x200;
	if (len != expected_length) {
		printf("Expected len %d, got %d\n", expected_length, len);
	}

	struct FPContext ctx = {
		.fp = fp1,
	};

	int of = 0x201;
	for (int i = 0; i < (int)n_props; i++) {
		uint32_t value;
		if ((of + (int)sizeof(uint32_t)) > len) {
			// Assume value will be zero if data structure cuts off before props list ends
			value = 0;
		} else {
			of += read_u32(bin + of, &value);
		}
		parse_prop(&ctx, i, value);
	}

	return 0;
}
