#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fp.h"

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

	struct FujiFP1 fp;

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

			free(buffer);
			fclose(f);
		}
	}
	closedir(dir);
	return 0;	
}

int main(int argc, char **argv) {
	//return parse_fp1_files();
	return parse_raw_files();

	return 0;
}
