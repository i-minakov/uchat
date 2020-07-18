#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	if (!sub || !str || !replace || !mx_strlen(str)) return NULL;

	if (!mx_strlen(sub) || !mx_strlen(replace) || mx_count_substr(str, sub) < 0) return (char *) str;
	
	char *rez = mx_strnew(mx_strlen(str) + mx_count_substr(str, sub) * (mx_strlen(replace) - mx_strlen(sub)));
	for (int i = 0, k = 0; i < mx_strlen(str); i++) {
		if (!mx_get_substr_index(&str[i], sub)) {
			for (int j = 0; j < mx_strlen(replace); j++, k++) rez[k] = replace[j];
			i += mx_strlen(sub) - 1;
		} else rez[k] = str[i], k++;
	}
	return rez;
}
