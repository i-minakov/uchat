#include "../inc/libmx.h"

static void prtu(int c, int a, int b, int i) {
	for (int j = i; j >= 0; j--) {
		char s = 0;
		s = j == i ? (char) ((c >> (6 * j)) & a) | b : 
			(char) ((c >> (6 * j)) & 63) | 128;
		write(1, &s, 1);
	}
}

void mx_print_unicode(wchar_t c) {
	if (c < 128) write(1, &c, 1);
	else if (c < 2048) prtu((int) c, 31, 192, 1);
	else if (c < 65536) prtu((int) c, 15, 224, 2);
	else prtu((int) c, 7, 240, 3);
}
