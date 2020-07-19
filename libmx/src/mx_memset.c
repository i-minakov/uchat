#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
	for (unsigned char *dst = (unsigned char *)b; len--;) {
		*dst = c;
		dst++;
	}
	return b;
}
