#include "../inc/libmx.h"

char *mx_backjoin(char *src, char *d) {
    char *s = NULL;

    s = mx_strjoin(src, d);
    if (d != NULL) {
        free(d);
        d = NULL;
    }
    return s;
}


