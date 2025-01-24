// Copyright 2025 Daniel C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "fp.h"

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

int validate_prop(uint32_t value, void *output, struct FujiLookup *tbl) {
	// TODO: output should be uint32_t
	for (int i = 0; tbl[i].key != NULL; i++) {
		if (value == tbl[i].value) {
			((uint32_t *)output)[0] = value;
			return 0;
		}
	}
	return -1;
}

static int parse_prop(struct FPContext *ctx, int idx, uint32_t value) {
	printf("Parsing prop %x at offset %x\n", value, idx);
	switch (idx) {
	case 0:
		//fp1->prop1 = validate_prop(ctx, value, &list);
		return 0;
	case 1:
		//fp1->prop2 = validate_prop(ctx, value, &list);
		return 0;
	case 2:
		return validate_prop(value, &ctx->fp->ImageSize, fp_image_size);
	case 3:
		return validate_prop(value, &ctx->fp->ImageQuality, fp_image_quality);
	case 4:
		//fp1->prop5 = validate_prop(ctx, value, &list);
		return 0;
	case 5:
		//fp1->prop6 = validate_prop(ctx, value, &list);
		return 0;
	case 6:
		//fp1->prop7 = validate_prop(ctx, value, &list);
		return 0;
	case 7:
		return validate_prop(value, &ctx->fp->FilmSimulation, fp_film_sim);
	case 8:
		return validate_prop(value, &ctx->fp->GrainEffect, fp_grain_effect);
	case 9:
		//fp1->prop10 = validate_prop(ctx, value, &list);
		return 0;
	case 10:
		//fp1->WBShootCond = validate_prop(ctx, value, &list);
		return 0;
	case 11:
		return validate_prop(value, &ctx->fp->WhiteBalance, fp_white_balance);
	case 12:
		//fp1->WBShiftR = validate_prop(ctx, value, &list);
		return 0;
	case 13:
		//fp1->WBShiftB = validate_prop(ctx, value, &list);
		return 0;
	case 14:
		//fp1->WBColorTemp = validate_prop(ctx, value, &list);
		return 0;
	case 15:
		//fp1->HighlightTone = validate_prop(ctx, value, &list);
		return 0;
	case 16:
		//fp1->prop17 = validate_prop(ctx, value, &list);
		return 0;
	case 17:
		//fp1->prop18 = validate_prop(ctx, value, &list);
		return 0;
	case 18:
		return validate_prop(value, &ctx->fp->Sharpness, fp_range);
		//fp1->Sharpness = validate_prop(ctx, value, &list);
		return 0;
	case 19:
		//fp1->prop20 = validate_prop(ctx, value, &list);
		return 0;
	case 20:
		//fp1->prop21 = validate_prop(ctx, value, &list);
		return 0;
	case 21:
		return validate_prop(value, &ctx->fp->ColorSpace, fp_color_space);
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
		// ????
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
		int rc = parse_prop(&ctx, i, value);
		if (rc) {
			printf("Error parsing property of value %x at index %d\n", value, i);
		}
	}

	return 0;
}
