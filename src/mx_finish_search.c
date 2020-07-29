#include "../inc/header.h"

static void free_srch(t_search **s) {
    if (!s || !*s)
        return;
    t_search *i = *s;
    t_search *j = NULL;

    for (; i; ) {
        j = NULL;
        if (i->next)
            j = i->next;
        mx_strdel(&i->name);
        i->next = NULL;
        free(i);
        i = NULL;
        i = j;
    }
    *s = NULL;
}

void close_search(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    if (icon_pos == GTK_ENTRY_ICON_PRIMARY)
        return ;
    (void)entry;
    (void)event;
    gtk_widget_show(m->cap->burger_but_img);
    gtk_widget_show(m->cap->burger_but);
    gtk_widget_show(m->cap->my_photo);
    gtk_widget_show(m->cap->frame_for_my_photo);
    gtk_widget_show(m->cap->my_name);
    gtk_widget_hide(m->search);
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    burger_leave(NULL, NULL, m);
    if (m->flag_search == 3) 
        free_srch(&m->srch);
    if (m->flag_search == 1) {
        gtk_widget_destroy(m->grid_search);
        gtk_widget_show_all(mx_activ_us(m)->text_grid);
        mx_strdel(&m->search_str);
    }
    m->cmd = DEF;
}

