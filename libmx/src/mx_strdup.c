#include "libmx.h"

char *mx_strdup(const char *s1) {
	char *s2 = mx_strnew(mx_strlen(s1));
	int j = 0;

	for (int i = 0; s1 && s1[i] != '\0'; i++) {
		s2[i] = s1[i]; 
		j++;
	}
	s2[j] = '\0';
	return s2;
}
