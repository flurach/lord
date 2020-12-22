#include "helpers.h"

char *ftoa(char *fpath)
{
	FILE *fp = fopen(fpath, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0, SEEK_END);
	const size_t s = ftell(fp);
	rewind(fp);

	char *buf = malloc(s + 1);
	fread(buf, 1, s, fp);

	fclose(fp);
	return buf;
}
