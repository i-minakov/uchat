#include "../inc/uchat.h"

static void reset_time(char *time, t_user *i) {
    char **m = NULL;
    char *s = NULL;
    char *res = NULL;

    if (time == NULL)
        return;
    m = mx_strsplit(time, ' ');
    if (m == NULL)
        return;
    s = mx_strdup(m[3]);
    mx_del_strarr(&m);
    m = mx_strsplit(s, ':');
    res = mx_strpart(s, 5);
    if (res != NULL) {
        gtk_label_set_text(GTK_LABEL(i->l_time), res);
        free(res);
    }
    free(s);
    mx_del_strarr(&m);
}

void reset_l_mess(t_user *i) {
    char *s = NULL;
    char *t = NULL;

    if (i->msg->next == NULL) {
        gtk_label_set_text(GTK_LABEL(i->l_mess), "");
        return ;
    }
    t = i->msg->next->text;
    if (t && mx_strlen(t) > 15) {
        s = mx_strpart(t, 14);
        s = mx_delit_fre(s, "...");
        gtk_label_set_text(GTK_LABEL(i->l_mess), s);
        free(s);
    }
    else if (t && mx_strlen(t) > 0)
        gtk_label_set_text(GTK_LABEL(i->l_mess), t);
    reset_time(i->msg->next->time, i);
}
