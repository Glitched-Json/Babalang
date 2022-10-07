#ifndef FILE_READER
#define FILE_READER
#include <stdio.h>

FILE* read_file(char* file_name) {
	if (file_name == NULL) {fprintf(stderr, "Trying to open file with NULL name\n"); return NULL;}
	FILE* fp = fopen(file_name, "r" );
    	if (fp == NULL) {fprintf(stderr, "File not found: %s\n", file_name); return NULL;}
    	return fp;
}

char* read_line(FILE* file) {
	char* c = (char *)malloc(sizeof(char) * 255);
	if (!fgets(c, 255, file)) return NULL;
	return c;
}

void file_close(FILE* file) {
	fclose(file);
}
#endif
