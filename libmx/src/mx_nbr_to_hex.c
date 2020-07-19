#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
	unsigned long arr = 0;
	for (unsigned long i = nbr; i > 0; i /= 16) {
		arr++;
	}
	char *str = mx_strnew(arr);
	int x = 0;
	for (int i = arr - 1; nbr > 0; i--) {
		x = nbr % 16;
		if (x == 10) str[i] = 'a';
		else if (x == 11) str[i] = 'b';
		else if (x == 12) str[i] = 'c';
		else if (x == 13) str[i] = 'd';
		else if (x == 14) str[i] = 'e';
		else if (x == 15) str[i] = 'f';
		else str[i] = x + '0';
		nbr = nbr / 16;
	}
	return str;
}
