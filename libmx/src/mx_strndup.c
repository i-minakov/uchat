#include "libmx.h"

char *mx_strndup(const char *s1, size_t n){
	size_t z = mx_strlen(s1);
	char *s2;
	if (n >= z) {
		s2 = mx_strnew(z);
		for (size_t i = 0; i < z; i++) s2[i] = s1[i];
	} else {
		s2 = mx_strnew(n);
		for (size_t i = 0; i < n; i++) s2[i] = s1[i];
	}
	
	return s2;
}
