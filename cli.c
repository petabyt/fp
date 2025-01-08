#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fp.h"

int main(int argc, char **argv) {
	const char *folder_path = "fp1";
	DIR *dir = opendir(folder_path);
	if (!dir)
		return -1;

	struct FujiFP1 fp;

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		char file_path[1024];
		if (entry->d_type == DT_REG) {
			snprintf(file_path, sizeof(file_path), "%s/%s", folder_path, entry->d_name);
			int rc = fp_parse_fp1(file_path, &fp);
			if (rc) return rc;
		}
	}
	closedir(dir);

	return 0;
}
