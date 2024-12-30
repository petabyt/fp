#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "fp1.h"

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

static int parse_on_off(struct Context *ctx, const char *str, enum FujiOnOff *out) {
	if (!strcmp(str, "ON")) {
		*out = FP_ON;
	} else if (!strcmp(str, "OFF")) {
		*out = FP_OFF;
	} else {
		return -1;
	}
	return 0;
}

static int parse_bool(struct Context *ctx, const char *str, enum FujiBool *out) {
	if (!strcmp(str, "TRUE")) {
		*out = FP_TRUE;
	} else if (!strcmp(str, "TRUE")) {
		*out = FP_FALSE;
	} else {
		return -1;
	}
	return 0;
}

static int parse_grain_effect(struct Context *ctx, const char *str, enum FujiGrainEffect *out) {
	if (!strcmp(str, "OFF")) {
		*out = FP_GRAIN_OFF;
	} else if (!strcmp(str, "WEAK")) {
		*out = FP_GRAIN_WEAK;
	} else if (!strcmp(str, "STRONG")) {
		*out = FP_GRAIN_STRONG;
	} else {
		return -1;
	}
	return 0;
}

static int parse_grain_effect_size(struct Context *ctx, const char *str, enum FujiGrainEffectSize *out) {
	if (!strcmp(str, "SMALL")) {
		*out = FP_GRAIN_SIZE_SMALL;
	} else {
		return -1;
	}
	return 0;
}

static int parse_prop(struct Context *ctx, const char *key, const char *value) {
	if (!strcmp(key, "SerialNumber")) {
	} else if (!strcmp(key, "Editable")) {
		return parse_bool(ctx, value, &ctx->fp->Editable);
	} else if (!strcmp(key, "IOPCode")) {
		if (value == NULL) return -1;
		if (strlen(value) != 8) return -1;
		ctx->fp->IOPCode = strtoul(value, NULL, 16);
	} else if (!strcmp(key, "StructVer")) {
		
	} else if (!strcmp(key, "TetherRAWConditonCode")) {

	} else if (!strcmp(key, "SourceFileName")) {

	} else if (!strcmp(key, "Fileerror")) {

	} else if (!strcmp(key, "ShootingCondition")) {
		
	} else if (!strcmp(key, "FilmSimulation")) {
		
	} else if (!strcmp(key, "RotationAngle")) {
		if (value == NULL) return -1;
		ctx->fp->RotationAngle = strtoul(value, NULL, 0);
	} else if (!strcmp(key, "BlackImageTone")) {
		if (value == NULL) return -1;
		ctx->fp->BlackImageTone = strtoul(value, NULL, 0);
	} else if (!strcmp(key, "MonochromaticColor_RG")) {
		if (value == NULL) return -1;
		ctx->fp->MonochromaticColor_RG = strtoul(value, NULL, 0);
	} else if (!strcmp(key, "MonochromaticColor_RG")) {
		if (value == NULL) return -1;
		ctx->fp->MonochromaticColor_RG = strtoul(value, NULL, 0);
	} else if (!strcmp(key, "GrainEffect")) {
		if (value == NULL) return -1;
		return parse_grain_effect(ctx, value, &ctx->fp->GrainEffect);
	} else if (!strcmp(key, "GrainEffectSize")) {
		if (value == NULL) return -1;
		return parse_grain_effect_size(ctx, value, &ctx->fp->GrainEffectSize);
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

int main(int argc, char **argv) {
	xmlDoc *doc = xmlReadFile("test/Street.FP1", NULL, 0);
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

	struct FujiFP1 fp1;
	struct Context ctx;
	ctx.fp = &fp1;

	int rc = parse_prop_group(&ctx, prop_group);
	if (rc) return rc;

	xmlFreeDoc(doc);
	xmlCleanupParser();
	return 0;
}
