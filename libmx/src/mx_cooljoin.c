#include "../inc/libmx.h"

char *mx_cooljoin(char *src, char *d) {
    char *s = NULL;

    s = mx_strjoin(src, d);
    if (src != NULL) {
        free(src);
        src = NULL;
    }
    if (d != NULL) {
        free(d);
        d = NULL;
    }
    return s;
}

