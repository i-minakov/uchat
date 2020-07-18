#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
	unsigned char *d = (unsigned char *)dst;
	unsigned char *s = (unsigned char *)src;
	for ( ; n--; ) {
		if (*s == c) {
			*d = *s;
			d++;
			return d;
		}
		*d = *s;
		d++;
		s++;
	}
	return NULL;
}
