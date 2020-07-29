#include "../inc/header.h"

/* search all */
void show_result_of_search(t_list *list, t_main *m) {
    if (m->flag_search == 1)
        result_msg(list, m);
    if (m->flag_search == 3)
        result_contacts(list, m);
    m->cmd = BLCK;
}

static void search_msg(GtkEntry *e, t_main *m) {
    char *s = NULL;

    (void)e;
    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return ;
    m->grid_search = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_search), 8);
    gtk_fixed_put(GTK_FIXED(m->fix_for_text), m->grid_search, 0, 0);
    mx_idle_show(true, m->grid_search);
    m->command = mx_arrjoin(m->command, "mx_update");
    m->command = mx_arrjoin(m->command, "history");
    m->command = mx_arrjoin(m->command, "search");
    m->search_str = mx_strdup(s);
    m->cmd = SRCH_MSG;
}

static void search_user(GtkEntry *e, t_main *m) {
    char *s = NULL;

    (void)e;
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return;
    for (t_user *i = m->users; i; i = i->next) {
        if (!mx_strstr(i->name, s))
            gtk_widget_destroy(i->fix);
    }
    burger_leave(NULL, NULL, m);
}

static void search_contacts(GtkEntry *e, t_main *m) {
    char *s = (char *)gtk_entry_get_text(e);

    (void)e;
    if (s == NULL || !mx_strlen(s))
        return ;
    m->command = mx_arrjoin(m->command, "mx_user_search");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, s);
    m->cmd = SRCH_US;
}

void search_activ(GtkEntry *e, t_main *m) {
    (void)e;
    if (m->flag_search == 1)
        search_msg(e, m);
    else if (m->flag_search == 2)
        search_user(e, m);
    else if (m->flag_search == 3)
        search_contacts(e, m);
}
