#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fp.h"

static void dump_property(const char *label, uint32_t value, struct FujiLookup *tbl) {
	if (tbl == NULL) {
		printf("%s = %x\n", label, value);
	}
}

void dump_struct(struct FujiFP1 *fp) {
	dump_property("IOPCode", fp->IOPCode, NULL);
	dump_property("TetherRAWConditonCode", fp->TetherRAWConditonCode, NULL);
	dump_property("Editable", fp->Editable, NULL);
	dump_property("ShootingCondition", fp->ShootingCondition, NULL);
	dump_property("FileType", fp->FileType, NULL);
	dump_property("ImageSize", fp->ImageSize, NULL);
	dump_property("RotationAngle", fp->RotationAngle, NULL);
	dump_property("ImageQuality", fp->ImageQuality, NULL);
	dump_property("ExposureBias", fp->ExposureBias, NULL);
	dump_property("DynamicRange", fp->DynamicRange, NULL);
	dump_property("WideDRange", fp->WideDRange, NULL);
	dump_property("FilmSimulation", fp->FilmSimulation, NULL);
	dump_property("BlackImageTone", fp->BlackImageTone, NULL);
	dump_property("MonochromaticColor_RG", fp->MonochromaticColor_RG, NULL);
	dump_property("GrainEffect", fp->GrainEffect, NULL);
	dump_property("GrainEffectSize", fp->GrainEffectSize, NULL);
	dump_property("ChromeEffect", fp->ChromeEffect, NULL);
	dump_property("ColorChromeBlue", fp->ColorChromeBlue, NULL);
	dump_property("SmoothSkinEffect", fp->SmoothSkinEffect, NULL);
	dump_property("WBShootCond", fp->WBShootCond, NULL);
	dump_property("WhiteBalance", fp->WhiteBalance, NULL);
	dump_property("WBShiftR", fp->WBShiftR, NULL);
	dump_property("WBShiftB", fp->WBShiftB, NULL);
	dump_property("WBColorTemp", fp->WBColorTemp, NULL);
	dump_property("HighlightTone", fp->HighlightTone, NULL);
	dump_property("ShadowTone", fp->ShadowTone, NULL);
	dump_property("Color", fp->Color, NULL);
	dump_property("Sharpness", fp->Sharpness, NULL);
	dump_property("NoisReduction", fp->NoisReduction, NULL);
	dump_property("Clarity", fp->Clarity, NULL);
	dump_property("LensModulationOpt", fp->LensModulationOpt, NULL);
	dump_property("ColorSpace", fp->ColorSpace, NULL);
	dump_property("HDR", fp->HDR, NULL);
}

int parse_fp1_files(void) {
	const char *folder_path = "fp1";
	DIR *dir = opendir(folder_path);
	if (!dir) return -1;

	struct FujiFP1 fp;

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		char file_path[1024];
		if (entry->d_type == DT_REG) {
			snprintf(file_path, sizeof(file_path), "%s/%s", folder_path, entry->d_name);
			printf("Parsing %s\n", file_path);
			int rc = fp_parse_fp1(file_path, &fp);
			if (rc) return rc;
		}
	}
	closedir(dir);
	return 0;
}

int parse_raw_files(void) {
	const char *folder_path = "raw";
	DIR *dir = opendir(folder_path);
	if (!dir) return -1;

	struct FujiFP1 fp = {0};

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		char file_path[1024];
		if (entry->d_type == DT_REG) {
			snprintf(file_path, sizeof(file_path), "%s/%s", folder_path, entry->d_name);
			printf("Parsing %s\n", file_path);

			FILE *f = fopen(file_path, "rb");
			if (f == NULL) return -1;

			fseek(f, 0, SEEK_END);
			long file_size = ftell(f);
			fseek(f, 0, SEEK_SET);

			uint8_t *buffer = malloc(file_size);
			fread(buffer, 1, file_size, f);

			int rc = fp_parse_raw(buffer, (int)file_size, &fp);
			if (rc) return rc;

			dump_struct(&fp);

			free(buffer);
			fclose(f);
		}
	}
	closedir(dir);
	return 0;	
}

int main(int argc, char **argv) {
//	parse_fp1_files();
	parse_raw_files();
	return 0;
}
