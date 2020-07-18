#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
	int count = 0;
	int z = mx_strlen(s1);
	for (int i = z, j = 0; s2[j]; i++, j++) {
		s1[i] = s2[j];
		count++;
	}
	s1[count + z] = '\0';
	return s1;
}
