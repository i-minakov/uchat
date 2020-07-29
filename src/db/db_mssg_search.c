#include "../../inc/header.h"

/* message search */
static void mx_copy_struct(t_history **first, t_history *second) {
    *first = (t_history *)malloc(sizeof(t_history));
    (*first)->id = second->id;
    (*first)->message = mx_strdup(second->message);
    (*first)->time = mx_strdup(second->time);
    (*first)->name = mx_strdup(second->name);
    (*first)->mssg_id = mx_strdup(second->mssg_id);
    (*first)->forward = mx_strdup(second->forward);
    (*first)->file_name = mx_strdup(second->file_name);
    (*first)->flag = mx_strdup(second->flag);
    (*first)->r_f_mssg = NULL;
    (*first)->r_f_time = NULL;
}

t_list *mx_mssg_search(char *name, char *another_name,
                       char *part_mssg, char *size) {
    if (!name || !another_name || !part_mssg)
        return NULL;
    t_list *list = mx_history_back(name, another_name, NULL);
    t_list *true_list = NULL;

    for (t_list *node = list; node; node = node->next) {
        if (mx_part_cmp(((t_history *)node->data)->message,
                        part_mssg)) {
            t_history *copy = NULL;

            mx_copy_struct(&copy, (t_history *)node->data);
            mx_push_front(&true_list, (void *)copy);
        }
        mx_free_history((t_history *)node->data);
    }
    mx_free_list(&list);
    mx_trim_for_size(&true_list, size);
    return true_list;
}

