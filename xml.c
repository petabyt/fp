// Copyright 2025 Daniel C
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "fp.h"

struct Context {
	struct FujiFP1 *fp;
};

const char *eval_iop_code(uint32_t code) {
	// ???
	switch (code) {
	case 0xFF159501:
		return "X Processor 4";
	}
	return "???";
}

struct FujiLookup {
	char *key;
	uint32_t value;
};

static int validate_lookup(struct Context *ctx, const char *str, void *out, struct FujiLookup *tbl, size_t tbl_size) {
	uint32_t *out_u32 = out;
	int n = tbl_size / sizeof(struct FujiLookup);
	for (int i = 0; i < n; i++) {
		if (!strcmp(str, tbl[i].key)) {
			(*out_u32) = tbl[i].value;
			return 0;
		}
	}
	return -1;
}
struct FujiLookup fp_on_off[] = {
	{"ON", FP_ON},
	{"OFF", FP_OFF},
};
struct FujiLookup fp_bool[] = {
	{"TRUE", FP_TRUE},
	{"FALSE", FP_FALSE},
};
struct FujiLookup fp_grain_effect[] = {
	{"OFF", FP_GRAIN_OFF},
	{"WEAK", FP_GRAIN_WEAK},
	{"STRONG", FP_GRAIN_STRONG},
};
struct FujiLookup fp_chrome_effect[] = {
	{"OFF", FP_CHROME_OFF},
	{"WEAK", FP_CHROME_WEAK},
	{"STRONG", FP_CHROME_STRONG},
};
struct FujiLookup fp_file_type[] = {
	{"JPG", FP_JPG},
};
struct FujiLookup fp_grain_effect_size[] = {
	{"SMALL", FP_GRAIN_SIZE_SMALL},
};
struct FujiLookup fp_image_size[] = {
	{"L3x2", FP_L3x2},
};
struct FujiLookup fp_image_quality[] = {
	{"Fine", FP_FINE},
};
struct FujiLookup fp_exposure_bias[] = {
	{"0", 0},
	{"P0P67", 1},
	{"P0P33", 2}, // ????
};
struct FujiLookup fp_white_balance[] = {
	{"AsShot", FP_WB_AsShot},
	{"INVALID", 1},
	{"Auto", FP_WB_Auto},
	{"Temperature", FP_WB_Temperature},
	{"Daylight", FP_WB_Daylight},
	{"FLight1", 123}, // ???
};
struct FujiLookup fp_color_temp[] = {
	{"0K", 0},
	{"3200K", 3200},
	{"5900K", 5900},
	{"8300K", 8300},
	{"10000K", 10000},
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
};
struct FujiLookup fp_color_space[] = {
	{"sRGB", 1},
	// TODO
};

static int parse_prop(struct Context *ctx, const char *key, const char *value) {
	if (!strcmp(key, "SerialNumber")) {
	} else if (!strcmp(key, "Editable")) {
		return validate_lookup(ctx, value, &ctx->fp->Editable, fp_bool, sizeof(fp_bool));
	} else if (!strcmp(key, "IOPCode")) {
		if (value == NULL) return -1;
		if (strlen(value) != 8) return -1;
		ctx->fp->IOPCode = strtoul(value, NULL, 16);
	} else if (!strcmp(key, "StructVer")) {
		
	} else if (!strcmp(key, "FileType")) {
		return validate_lookup(ctx, value, &ctx->fp->FileType, fp_file_type, sizeof(fp_file_type));
	} else if (!strcmp(key, "ImageSize")) {
		return validate_lookup(ctx, value, &ctx->fp->ImageSize, fp_image_size, sizeof(fp_image_size));
	} else if (!strcmp(key, "ImageQuality")) {
		return validate_lookup(ctx, value, &ctx->fp->ImageQuality, fp_image_quality, sizeof(fp_image_quality));
	} else if (!strcmp(key, "ExposureBias")) {
		return validate_lookup(ctx, value, &ctx->fp->ExposureBias, fp_exposure_bias, sizeof(fp_exposure_bias));
	} else if (!strcmp(key, "ChromeEffect")) {
		return validate_lookup(ctx, value, &ctx->fp->ChromeEffect, fp_chrome_effect, sizeof(fp_chrome_effect));
	} else if (!strcmp(key, "WhiteBalance")) {
		return validate_lookup(ctx, value, &ctx->fp->WhiteBalance, fp_white_balance, sizeof(fp_white_balance));
	} else if (!strcmp(key, "WBColorTemp")) {
		return validate_lookup(ctx, value, &ctx->fp->WBColorTemp, fp_color_temp, sizeof(fp_color_temp));
	} else if (!strcmp(key, "WBShiftR")) {
		if (value == NULL) return -1;
		int val = (int)strtoul(value, NULL, 0);
		if (!(val >= -10 && val <= 10)) return -1;
		ctx->fp->WBShiftR = val;
	} else if (!strcmp(key, "WBShiftB")) {
		if (value == NULL) return -1;
		int val = (int)strtoul(value, NULL, 0);
		if (!(val >= -10 && val <= 10)) return -1;
		ctx->fp->WBShiftR = val;
	} else if (!strcmp(key, "HighlightTone")) {
		return validate_lookup(ctx, value, &ctx->fp->Color, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "ShadowTone")) {
		return validate_lookup(ctx, value, &ctx->fp->Color, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "Color")) {
		return validate_lookup(ctx, value, &ctx->fp->Color, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "Sharpness")) {
		return validate_lookup(ctx, value, &ctx->fp->Sharpness, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "NoisReduction")) {
		return validate_lookup(ctx, value, &ctx->fp->NoisReduction, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "Clarity")) {
		return validate_lookup(ctx, value, &ctx->fp->Clarity, fp_range, sizeof(fp_range));
	} else if (!strcmp(key, "TetherRAWConditonCode")) {
		// TODO
	} else if (!strcmp(key, "SourceFileName")) {
		// TODO
	} else if (!strcmp(key, "Fileerror")) {
		// TODO
	} else if (!strcmp(key, "ShootingCondition")) {
		// TODO
	} else if (!strcmp(key, "FilmSimulation")) {
		// TODO
	} else if (!strcmp(key, "RotationAngle")) {
		if (value == NULL) return -1;
		ctx->fp->RotationAngle = (int)strtoul(value, NULL, 0);
	} else if (!strcmp(key, "DynamicRange")) {
		if (value == NULL) return -1;
		ctx->fp->DynamicRange = (int)strtoul(value, NULL, 0);
		if (!(ctx->fp->DynamicRange >= 0 && ctx->fp->DynamicRange <= 100)) {
			return -1;
		}
	} else if (!strcmp(key, "WideDRange")) {
		if (value == NULL) return -1;
		uint32_t v = (int)strtoul(value, NULL, 0);
		if (!(v >= 0 && v <= 100)) {
			return -1;
		}
		ctx->fp->WideDRange = v;
	} else if (!strcmp(key, "BlackImageTone")) {
		if (value == NULL) return -1;
		ctx->fp->BlackImageTone = (int)strtoul(value, NULL, 0);
	} else if (!strcmp(key, "MonochromaticColor_RG")) {
		if (value == NULL) return -1;
		ctx->fp->MonochromaticColor_RG = (int)strtoul(value, NULL, 0); // TODO Was gonna do sometyhing here
	} else if (!strcmp(key, "MonochromaticColor_RG")) {
		if (value == NULL) return -1;
		ctx->fp->MonochromaticColor_RG = (int)strtoul(value, NULL, 0);
	} else if (!strcmp(key, "GrainEffect")) {
		return validate_lookup(ctx, value, &ctx->fp->GrainEffect, fp_grain_effect, sizeof(fp_grain_effect));
	} else if (!strcmp(key, "GrainEffectSize")) {
		return validate_lookup(ctx, value, &ctx->fp->GrainEffectSize, fp_grain_effect_size, sizeof(fp_grain_effect_size));
	} else if (!strcmp(key, "ColorChromeBlue")) {
		// TODO NULL, or "WEAK"
	} else if (!strcmp(key, "HDR")) {
		if (value != NULL) return -1;
		ctx->fp->HDR = FP_ON;
	} else if (!strcmp(key, "SmoothSkinEffect")) {
		if (value != NULL) return -1;
		ctx->fp->SmoothSkinEffect = FP_ON;
	} else if (!strcmp(key, "WBShootCond")) {
		return validate_lookup(ctx, value, &ctx->fp->WBShootCond, fp_on_off, sizeof(fp_on_off));
	} else if (!strcmp(key, "LensModulationOpt")) {
		return validate_lookup(ctx, value, &ctx->fp->WBShootCond, fp_on_off, sizeof(fp_on_off));
	} else if (!strcmp(key, "ColorSpace")) {
		return validate_lookup(ctx, value, &ctx->fp->ColorSpace, fp_color_space, sizeof(fp_color_space));
	} else {
		printf("TODO: %s\n", key);
		return -1;
	}
	return 0;
}

static int parse_prop_group(struct Context *ctx, xmlNode *node) {
	xmlNode *cur = NULL;
	for (cur = node; cur; cur = cur->next) {
		if (cur->type != XML_ELEMENT_NODE) {
			printf("%d\n", cur->type);
			return -1;
		}

		const char *name = (const char *)cur->name;
		const char *value = NULL;
		if (cur->children != NULL && cur->children->content != NULL) {
			value = (const char *)cur->children->content;
		}

		cur = cur->next;
		if (cur == NULL) return -1;

		int rc = parse_prop(ctx, name, value);
		if (rc) {
			printf("Error parsing prop '%s' = '%s'\n", name, value);
			return rc;
		}
		
		if (cur->children) {
			xmlNode *tags = cur->children;
			for (; tags; tags = tags->next) {
				printf("%s\n", tags->name);
			}
			continue;
		}
	}
	return 0;
}

int fp_parse_fp1(const char *path, struct FujiFP1 *fp1) {
	xmlDoc *doc = xmlReadFile(path, NULL, 0);
	if (doc == NULL) {
		fprintf(stderr, "Could not parse file: %s\n", "");
		return 1;
	}

	xmlNode *root = xmlDocGetRootElement(doc);
	if (root == NULL) {
		return -1;
		//xmlFreeDoc(doc);
	}

	//printf("Root Element: %s\n", root->name);
	if (strcmp((const char *)root->name, "ConversionProfile")) {
		abort();
	}
	xmlNode *group = root->children->next;
	if (strcmp((const char *)group->name, "PropertyGroup")) {
		printf("%s\n", group->name);
		abort();
	}

	xmlNode *prop_group = group->children->next;

	struct Context ctx;
	memset(fp1, 0, sizeof(struct FujiFP1));
	ctx.fp = fp1;

	int rc = parse_prop_group(&ctx, prop_group);
	if (rc) return rc;

	xmlFreeDoc(doc);
	xmlCleanupParser();
	return 0;	
}
