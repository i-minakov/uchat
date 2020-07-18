#include "uchat.h"

char *mx_strpart(char *str, int index) {
    char *res = NULL;
    int len = mx_strlen(str);

    if (str == NULL)
        return NULL;
    res = mx_strnew(len - (len - index) + 1);
    for (int i = 0; str[i] && i < index; i++)
        res[i] = str[i];
    return res;
}
