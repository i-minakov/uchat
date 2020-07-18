#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	if (!str || !sub) return -2;
	int z = mx_strlen(sub);
	int count = 0;
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
				int d = 0;
				while (d < i) {
					d++;
				}
				return d;
			}
		}
	}
	return -1;
}
