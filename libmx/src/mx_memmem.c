#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	if ((big_len <= 0) || (little_len <= 0)) return NULL;
	unsigned char *b = (unsigned char *)big;
	unsigned char *l = (unsigned char *)little;
	size_t count = 0;
	for (size_t i = 0; i < big_len; i++) {
		if (b[i] == l[0]) {
			count = 0;
			for (size_t j = 0; j < little_len; j++) if (b[i + j] == l[j]) count++;
			if (count == little_len) {
				for (size_t z = 0; z < i; z++) b++;
				return b;
			}
		}
	}
	return NULL;
}
