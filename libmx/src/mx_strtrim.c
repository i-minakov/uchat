#include "libmx.h"

static bool own_isspace(char c) {
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

char *mx_strtrim(const char *str) {
	if (str == NULL) return NULL;
	int left;
	int right;
	left = 0;
	right = mx_strlen(str);
	for (int i = 0; own_isspace(str[i]); i++, left++);
	for (int i = mx_strlen(str) - 1; own_isspace(str[i]); i--, right--);
	if (right - left < 0) return mx_strncpy((char *) malloc(1 * sizeof(char)), str, 0);
	char *p = mx_strnew(right - left);
	p = mx_strncpy(p, &str[left], right - left);
	return p;
}
