#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "exit.h"
#include "parse.h"

const char *load_file(const char *filename) {
	long int ftell_result;

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		errx(EXIT_CANNOT_READ_FILE, "Unable to open file at %s", filename);
	}

	if (fseek(fp, 0, SEEK_END) != 0) {
		errx(EXIT_CANNOT_READ_FILE, "Unable to seek to end of file at %s",
		     filename);
	}

	if ((ftell_result = ftell(fp)) < 0) {
		errx(EXIT_CANNOT_READ_FILE, "Unable to get size of file at %s",
		     filename);
	}

	if (ftell_result > SIZE_MAX || ftell_result < 0) {
		errx(EXIT_CANNOT_READ_FILE, "Size of file at %s is too big for memory",
		     filename);
	}

	size_t length = (size_t)ftell_result;

	if (fseek(fp, 0, SEEK_SET) != 0) {
		errx(EXIT_CANNOT_READ_FILE, "Unable to seek to start of file at %s",
		     filename);
	}

	char *file_contents = malloc(length);
	CHECK_MALLOC(file_contents, "input file contents");
	return file_contents;
}
