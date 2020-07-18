#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
	for (unsigned long i = 0; i < n; i++) {
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return dst;
}
