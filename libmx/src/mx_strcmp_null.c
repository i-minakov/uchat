#include "../inc/../inc/libmx.h"

int mx_strcmp_null(const char *s1, const char *s2) {
    int i = 0;

    if (s1 == NULL)
        return -1;
    if (s2 == NULL)
        return 1;

    while ((s1[i] && s2[i]) && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
