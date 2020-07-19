#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
	if (!str) return -1;
	int d = 0;
	if ((str[0] != c) && (str[0] != '\0')) d++;
	for (int i = 0; str[i]; i++) {
		if ((str[i] == c) && (str[i + 1] != c) && (str[i + 1] != '\0')) {
			d++;
		}
	}
	return d;
}
