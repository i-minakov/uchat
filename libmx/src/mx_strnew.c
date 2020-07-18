#include "libmx.h"

char *mx_strnew(const int size) {
	if (size < 0) return NULL;
	char *p;
	p = (char*)malloc(size + 1);
	if (!p) return NULL;
	for (int i = 0; i <= size; i++) p[i] = '\0';
	return p;
}
