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
	switch (idx) {
	case 0:
		// Asuming ShootingCondition
		//fp1->prop1 = validate_prop(ctx, value, &list);
		return 0;
	case 1:
		// Assuming this is FileType
		//fp1->prop2 = validate_prop(ctx, value, &list);
		return 0;
	case 2:
		return validate_prop(value, &ctx->fp->ImageSize, fp_image_size);
	case 3:
		return validate_prop(value, &ctx->fp->ImageQuality, fp_image_quality);
	case 4:
		return validate_prop(value, &ctx->fp->ExposureBias, fp_exposure_bias);
	case 5:
		return validate_prop(value, &ctx->fp->DynamicRange, fp_drange);
	case 6:
		return validate_prop(value, &ctx->fp->WideDRange, fp_drange_priority);
	case 7:
		return validate_prop(value, &ctx->fp->FilmSimulation, fp_film_sim);
	case 8:
		return validate_prop(value, &ctx->fp->GrainEffect, fp_grain_effect);
	case 9:
		ctx->fp->SmoothSkinEffect = value; // TODO
		return 0;
	case 10:
		ctx->fp->WBShootCond = value; // TODO
		return 0;
	case 11:
		return validate_prop(value, &ctx->fp->WhiteBalance, fp_white_balance);
	case 12:
		return validate_prop(value, &ctx->fp->WBShiftR, fp_range);
	case 13:
		return validate_prop(value, &ctx->fp->WBShiftB, fp_range);
	case 14:
		return validate_prop(value, &ctx->fp->WBColorTemp, fp_color_temp);
	case 15:
		return validate_prop(value, &ctx->fp->HighlightTone, fp_range_p4_n2);
	case 16:
		return validate_prop(value, &ctx->fp->ShadowTone, fp_range_p4_n2);
	case 17:
		return validate_prop(value, &ctx->fp->Color, fp_range);
	case 18:
		return validate_prop(value, &ctx->fp->Sharpness, fp_range);
	case 19:
		return validate_prop(value, &ctx->fp->NoisReduction, fp_noise_reduction);
	case 20:
		return validate_prop(value, &ctx->fp->Clarity, fp_clarity);
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

int fp_parse_d185(const uint8_t *bin, int len, struct FujiFP1 *fp1) {
	if (len < 0x200) return -1;

	const struct FujiBinaryProfile *profile = (const struct FujiBinaryProfile *)bin;

	uint16_t n_props;
	read_u16(&profile->n_props, &n_props);

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
			return -1;
		}
	}

	return 0;
}
