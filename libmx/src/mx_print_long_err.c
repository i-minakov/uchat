#include "libmx.h"

void mx_print_long_err(char *s1, char *s2, char *s3, char *s4) {
    if (s1)
        write(2, s1, mx_strlen(s1));
    if (s2)
        write(2, s2, mx_strlen(s2));
    if (s3)
        write(2, s3, mx_strlen(s3));
    if (s4)
        write(2, s4, mx_strlen(s4));
}
