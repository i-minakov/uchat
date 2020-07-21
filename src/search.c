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
    burger_leave(NULL, NULL, m);
}

static void search_contacts(GtkEntry *e, t_main *m) {
    char *s = (char *)gtk_entry_get_text(e);

    if (s == NULL)
        return ;
    m->command = mx_arrjoin(m->command, "mx_add_user_to_table");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, s);
    m->command = mx_arrjoin(m->command, "1");
    user_pushback(&m->users, s);
    set_users(m);
    set_chat_grid(m);
}
 
void search_activ(GtkEntry *e, t_main *m) {
    if (m->flag_search == 1)
        search_msg(e, m);
    // else if (m->flag_search == 2)
    //     search_user(e, m);
    else if (m->flag_search == 2)
        search_contacts(e, m);
}
