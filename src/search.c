#include "../inc/uchat.h"

static void search_msg(GtkEntry *e, t_main *m) {
    t_user *us = NULL;
    char *s = NULL;

    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return ;
    for (t_user *i = m->users; i; i = i->next)
        (i->check == true) ? us = i : 0;
    for (t_msg *i = us->msg; i; i = i->next) {
        if (!mx_strcmp_null(i->text, s)) {
           gtk_adjustment_set_value(m->adj, i->adj_value + 150.0);
           printf("adj now === %f\n", gtk_adjustment_get_value(m->adj));
           return ;
        }
    }
    for (t_msg *i = us->msg; i; i = i->next) {
        if (mx_get_substr_index(i->text, s) > -1) {
           gtk_adjustment_set_value(m->adj, i->adj_value + 150.0);
           printf("adj now === %f\n", gtk_adjustment_get_value(m->adj));
           return ;
        }
    }
}

static void search_user(GtkEntry *e, t_main *m) {
    char *s = NULL;

    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return ;
    for (t_user *i = m->users; i; i = i->next) {
        if (!mx_strstr(i->name, s))
            gtk_widget_destroy(i->fix);
    }
}

void search_activ(GtkEntry *e, t_main *m) {
    if (m->flag_search == 1)
        search_msg(e, m);
    else if (m->flag_search == 2)
        search_user(e, m);
}
