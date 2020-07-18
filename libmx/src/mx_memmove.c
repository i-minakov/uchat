#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
	if ((len <= 0) || (dst == src)) return dst;
	unsigned char *d = (unsigned char *)dst;
	unsigned char *s = (unsigned char *)src;

	if (dst > src) {
		size_t n = len;
		while (len--) d++, s++;
		d--, s--, n--;
		for (; n--;d--, s--) {
			*d = *s;
		}
		*d = *s;
		return dst;
	}

	if (dst < src) {
		for (; len--;d++, s++) {
			*d = *s;
		}
		return dst;
	}
	return dst;
}
