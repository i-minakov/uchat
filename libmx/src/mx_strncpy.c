#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
	for (int i = 0; i < len; i++) {
		if (src[i] == '\0') {
			for (int j = i; j < len; j++) dst[j] = '\0';
			return dst;
		}
		dst[i] = src[i];
	}
	return dst;
}
