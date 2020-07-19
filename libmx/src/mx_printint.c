#include "../inc/libmx.h"

void mx_printint(int n) {
	if (n == -2147483648) {
		write(1, "-2147483648", 11);
	}
	else if (n == 0) write(1, "0",1);
	else {
		int min = n;
		if (min < 0) {
			write(1, "-",1);
			n *= -1;
		}
		int len = 0;
		for (int i = n; i != 0; i /= 10) {
			len++;
		}
		char s[len];
		s[len] = '\0';
		int ost = 0;
		for (int i = len - 1; i >= 0; i--) {
			ost = n % 10;
			s[i] = ost + '0';
			n = n / 10;
		}
		for (int i = 0; s[i] != '\0'; i++) {
			mx_printchar(s[i]);
		}
	}
}
