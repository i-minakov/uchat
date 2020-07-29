#include "../../inc/header.h"

static int mx_switch_time(int i, char **arr1, char **arr2) {
    switch(i) {
        case 1:
            return mx_intcmp(arr1[4], arr2[4]);
        case 2:
            return mx_monthcmp(arr1[1], arr2[1]);
        case 3:
            return mx_intcmp(arr1[2], arr2[2]);
        case 4:
            return mx_intcmp(arr1[0], arr2[0]);
        case 5:
            return mx_intcmp(arr1[1], arr2[1]);
        case 6:
            return mx_intcmp(arr1[2], arr2[2]);
        default:
            return 0;
    }
}

static void mx_change_cmp(char ***arr) {
    if (!arr || !*arr)
        return;
    char **shift = mx_strsplit((*arr)[3], ':');

    mx_del_strarr(&(*arr));
    *arr = shift;
}

static int mx_parse_time(char *str1, char *str2) {
    int result = 0;
    char **arr1 = mx_strsplit(str1, ' ');
    char **arr2 = mx_strsplit(str2, ' ');

    if (!arr1 || !arr2)
        return 0;
    for (int i = 0; i < 6; i++) {
        if (i == 3) {
            mx_change_cmp(&arr1);
            mx_change_cmp(&arr2);
        }
        if ((result = mx_switch_time(i + 1, arr1, arr2)) != 0)
            break;
    }
    mx_del_strarr(&arr1);
    mx_del_strarr(&arr2);
    return result;
}

int mx_pre_parse_time(char *json1, char *json2) {
    if (!json1 || !json2)
        return 0;
    int result = 0;
    char **arr1 = mx_get_arr(json1);
    char **arr2 = mx_get_arr(json2);

    if (!arr1 || !arr2)
        return 0;
    result = mx_parse_time(arr1[1], arr2[1]);
    mx_del_strarr(&arr1);
    mx_del_strarr(&arr2);
    return result;
}

