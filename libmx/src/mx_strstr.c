#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
	if (!mx_strlen(needle)) return (char *) haystack;
	for ( ; *haystack; haystack++) 
		for (int i = 0; haystack[i] == needle[i]; i++) if (i == mx_strlen(needle) - 1) return (char *) haystack;
	return NULL;
}
