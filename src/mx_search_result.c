#include "../inc/header.h"

/* result of search */
void add_contact_to_us(GtkWidget *wid, t_search *s) {
    (void)wid;
    user_pushfront(&s->m->users, s->name, MX_DEF_PHOTO);
    set_chat_grid(s->m, 1);
    gtk_widget_destroy(s->but);
}

bool mx_user_exist(t_main *m, char *name) {
    for (t_user *i = m->users; i; i = i->next) 
        if (!mx_strcmp(i->name, name))
            return true;
    return false;
}

static GtkWidget *create_contacts(char *name, t_main *m, t_search *s) {
    GtkWidget *fix = gtk_fixed_new(); 
    char *markup = g_markup_printf_escaped(MX_NAME_COLOR(m->style->color), s->name);
    GtkWidget *l = gtk_label_new(NULL);

    s->but = gtk_button_new_with_label("Add");
    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SLEPT(m->style->color)), 11, 0);
    gtk_label_set_markup(GTK_LABEL(l), markup);
    gtk_fixed_put(GTK_FIXED(fix), resize_image(MX_DEF_PHOTO, 51, 51), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SL_PH(m->style->color)), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), l, 83, 25);
    if (!mx_user_exist(m, name)) {
        gtk_fixed_put(GTK_FIXED(fix), s->but, 210, 21);
        MX_SET_NAME_MSG(m->style->color, s->but);
        g_signal_connect(s->but, "clicked", G_CALLBACK(add_contact_to_us), s);
    }
    g_idle_add((GSourceFunc)mx_show, fix);
    g_free(markup);
    return fix;
}

void result_contacts(t_list *list, t_main *m) {
    int row = 0;

    gtk_widget_destroy(m->grid_user);
    m->grid_user = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_user), 8);
    for (t_list *i = list; i; i = i->next) {
        pushfront_search_contact(&m->srch, m, 
            ((t_data *)i->data)->name, ((t_data *)i->data)->path);
        gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
        gtk_grid_attach(GTK_GRID(m->grid_user), 
            create_contacts(m->srch->name, m, m->srch), 0, row++, 1, 1);
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_users), m->grid_user, 0, 8);
    g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
}

void result_msg(t_list *list, t_main *m) {
    int row = 0;
    t_user *us = mx_activ_us(m);
    GtkWidget *box;
    GtkWidget *l;
    char **arr = NULL;
    bool my = false;

    mx_idle_hide(false, us->text_grid);
    for (t_list *i = ((t_data *)list->data)->list; i->data; i = i->next) {
        arr = mx_get_arr(i->data);
        gtk_grid_insert_row(GTK_GRID(m->grid_search), row);
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_size_request(box, 650, 30);
        l = gtk_button_new_with_label(arr[TXT]);
        gtk_widget_set_size_request(box, 100, 30);
        !mx_strcmp(m->my_name, arr[NAME]) ? my = true : 0;
        MX_MSG_PACK(my, l, box);
        MX_SET_NAME_MSG(my, l);
        gtk_grid_attach(GTK_GRID(m->grid_search), box, 0, row++, 1, 1);
        mx_idle_show(false, box);
        my = false;
    }
    
}
