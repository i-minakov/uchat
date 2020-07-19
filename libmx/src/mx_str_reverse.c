#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
	int count = 0;
	for (int i = 0; s[i]; i++) count++;
	for (int i = 0, j = count - 1; i < count / 2; i++, j--) {
		mx_swap_char(&s[i], &s[j]);
	}
}
