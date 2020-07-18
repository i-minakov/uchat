#include "libmx.h"

char *mx_itoa(long int number) {
    long int i = 1;
    char *rez = NULL;
    
    if (number == 0) {
        rez = mx_strdup("0");
        return rez;
    }
    for (long n = (number < 0) ? (long) number * -1 : number; n;
        n /= 10, i++);
    i = number < 0 ? i++ : i - 1;
    rez = mx_strnew(i);
    for (long n = (number < 0) ? (long) number * -1 : number; n;
        rez[i - 1] = n % 10 + '0', n /= 10, i--);
    if (number < 0)
        rez[0] = '-';
    return rez;
}
