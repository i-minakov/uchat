#include "libmx.h"

static int mx_arrsize_malloc(char **arr) {
    int count = 2;

    if (!arr)
        return count;
    for (int i = 0; arr[i]; i++)
        count++;
    return count;
}

char **mx_arrjoin(char **arr, char *str) {
    char **new_arr = (char **)malloc(sizeof(char *) * mx_arrsize_malloc(arr));

    for (int i = 0; i < mx_arrsize_malloc(arr); i++) {
        if (i == mx_arrsize_malloc(arr) - 2)
            new_arr[i] = mx_strdup(str);
        else if (i == mx_arrsize_malloc(arr) - 1)
            new_arr[i] = NULL;
        else
            new_arr[i] = mx_strdup(arr[i]);
    }
    if (arr)
        mx_del_strarr(&arr);
    return new_arr;
}
