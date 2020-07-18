#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
	unsigned char *d = (unsigned char *)s1;
	unsigned char *s = (unsigned char *)s2;
	for ( ; n--; ) {
		if ((*d > *s) || (*d < *s)) return *d - *s;
		s++;
		d++;
	}
	return 0;
}
