#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char *s1 = (unsigned char*)s;
	unsigned long count = 0;
	for (; n--;) {
		if (*s1 == c) {
			return s1;
		}
		s1++;
		count++;
	}
	return NULL;
}
