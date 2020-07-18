#include "../inc/../inc/libmx.h"

char *mx_delit_fre(char *src, char *d) {
    char *s = NULL;

    s = mx_strjoin(src, d);
    if (src != NULL) {
        free(src);
        src = NULL;
    }
    return s;
}
