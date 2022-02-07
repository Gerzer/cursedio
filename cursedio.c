//
//  cursedio.c
//  cursedio
//
//  Created by Gabriel Jacoby-Cooper on 2/7/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "cursedio.h"

struct streams_t {
	FILE* stream;
	struct streams_t* prev;
};

struct streams_t* streams = NULL;

int copen(const char* path, const char* mode) {
	struct streams_t* streams_old = NULL;
	if (streams) {
		streams_old = streams;
	}
	streams = calloc(1, sizeof(struct streams_t));
	streams->prev = streams_old;
	streams->stream = fopen(path, mode);
	if (streams->stream) {
		return 0;
	} else {
		struct streams_t* streams_old = streams->prev;
		free(streams);
		streams = streams_old;
		return -1;
	}
}

int cclose() {
	int ret = fclose(streams->stream);
	struct streams_t* streams_old = streams->prev;
	free(streams);
	streams = streams_old;
	return ret;
}

int cgetc() {
	return fgetc(streams->stream);
}

int cputc(int c) {
	return fputc(c, streams->stream);
}

int cseek(long offset, int whence) {
	return fseek(streams->stream, offset, whence);
}

int cgetpos(fpos_t* pos) {
	return fgetpos(streams->stream, pos);
}

int csetpos(const fpos_t* pos) {
	return fsetpos(streams->stream, pos);
}

int cfastforward(void) {
	return fseek(streams->stream, 0, SEEK_END);
}

void crewind(void) {
	rewind(streams->stream);
}

int cscanf(const char* format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = fscanf(streams->stream, format, ap);
	va_end(ap);
	return ret;
}
