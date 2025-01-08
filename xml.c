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
	switch (code) {
	case 0xFF159501:
		return "X Processor 4";
	}
	// TODO
	return "???";
}

struct FujiLookup {
	char *key;
	uint32_t value;
};

struct FujiLookup fp_on_off[] = {
	{"ON", FP_ON},
	{"OFF", FP_OFF},
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
struct FujiLookup fp_bool[] = {
	{"TRUE", FP_TRUE},
	{"FALSE", FP_FALSE},
};
struct FujiLookup fp_grain_effect[] = {
	{"OFF", FP_GRAIN_OFF},
	{"WEAK", FP_GRAIN_WEAK},
	{"STRONG", FP_GRAIN_STRONG},
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
	} else if (!strcmp(key, "TetherRAWConditonCode")) {

	} else if (!strcmp(key, "SourceFileName")) {

	} else if (!strcmp(key, "Fileerror")) {

	} else if (!strcmp(key, "ShootingCondition")) {
		
	} else if (!strcmp(key, "FilmSimulation")) {
		
	} else if (!strcmp(key, "RotationAngle")) {
		if (value == NULL) return -1;
		ctx->fp->RotationAngle = (int)strtoul(value, NULL, 0);
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
		if (value != NULL) return -1;
		ctx->fp->ColorChromeBlue = FP_ON;
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
		if (rc) return rc;
		
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
