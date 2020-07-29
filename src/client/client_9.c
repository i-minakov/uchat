#include "../../inc/header.h"

/* sort */
int mx_intcmp(char *str1, char *str2) {
    int num1 = mx_atoi(str1);
    int num2 = mx_atoi(str2);

    if (num1 != num2)
        return num1 - num2;
    return 0;
}

int mx_monthcmp(char *month1, char *month2) {
    enum e_month {Jan, Feb, Mar, Apr, May, Jun,
                  Jul, Aug, Sep, Oct, Nov, Dec};
    static struct {char *m; enum e_month e;} map[] = {
        {"Jan", Jan}, {"Feb", Feb}, {"Mar", Mar}, {"Apr", Apr},
        {"May", May}, {"Jun", Jun}, {"Jul", Jul}, {"Aug", Aug},
        {"Sep", Sep}, {"Oct", Oct}, {"Nov", Nov}, {"Dec", Dec},};
    int num1 = 0;
    int num2 = 0;

    for (int i = 0; i < (int)(sizeof(map)/sizeof(map[0])); i++) {
        if (mx_strcmp(month1, map[i].m) == 0)
            num1 = map[i].e;
        if (mx_strcmp(month2, map[i].m) == 0)
            num2 = map[i].e;
    }
    if (num1 != num2)
        return num1 - num2;
    return 0;
}

static void mx_sort_mssg_adt(int flag, t_list *i,
                             char **str1, char **str2) {
    if (flag == 0) {
        *str1 = (char *)((t_data *)i->data)->list->data;
        *str2 = (char *)((t_data *)i->next->data)->list->data;
    }
    else if (flag == 1) {
        *str1 = ((t_data *)i->data)->name;
        *str2 = ((t_data *)i->next->data)->name;
    }
}

void mx_sort_mssg(t_list **list, int flag) {
    int out = 0;
    void *data = NULL;
    char *str1 = NULL;
    char *str2 = NULL;

    while (out == 0) {
        out = 1;
        for (t_list *i = *list; i && i->next; i = i->next) {
            mx_sort_mssg_adt(flag, i, &str1, &str2);
            if ((flag == 0 && mx_pre_parse_time(str1, str2) > 0)
                || (flag == 1 && mx_strcmp(str1, str2) > 0)) {
                data = i->data;
                i->data = i->next->data;
                i->next->data = data;
                data = NULL;
                out = 0;
            }
        }
    }
}

