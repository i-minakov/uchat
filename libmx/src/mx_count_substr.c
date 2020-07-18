#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
	if (!str || !sub) return -1;
	int z = mx_strlen(sub);
	int count = 0;
	int d = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == sub[0]) {
			for (int j = 0; sub[j]; j++) {
				if (str[i + j] == sub[j]) count++;
				else {
					count = 0;
					break;
				}
			}
			if (count == z) {
				d = d + 1;
				count = 0;
			}
		}
	}
	return d;
}
