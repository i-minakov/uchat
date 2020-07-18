#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
	unsigned int pp = 1;
	double y = n;
	if (pow == 0) return 1;
	for (; pp < pow; pp++) {
		y *= n;
	}
	return y;
}
