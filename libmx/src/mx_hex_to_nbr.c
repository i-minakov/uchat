#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	int count = 0;
	for (int i = 0; hex[i]; i++) {
		count++;
	}
	unsigned long int sum = 0;
	unsigned long int x = 0, stepen = 1;
	for (int i = 0; hex[i]; i++) {
		if (hex[i] == 'A' || hex[i] == 'a') x = 10;
		else if (hex[i] == 'B' || hex[i] == 'b') x = 11;
		else if (hex[i] == 'C' || hex[i] == 'c') x = 12;
		else if (hex[i] == 'D' || hex[i] == 'd') x = 13;
		else if (hex[i] == 'E' || hex[i] == 'e') x = 14;
		else if (hex[i] == 'F' || hex[i] == 'f') x = 15;
		else if (hex[i] > 47 && hex[i] < 58) x = hex[i] - '0';
		else return -1;

		if (count > 1) {
			stepen = 1;
			for (int j = count - 1; j > 0; j--) {
			stepen = stepen * 16;
			}
		}
		else if (count == 1) stepen = 1;
		sum = sum + x * stepen;
		count = count - 1;
	}
	return sum;
}
