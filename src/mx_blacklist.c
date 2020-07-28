#include "../inc/header.h"

static void mx_unblock_user(GtkWidget *wid, t_main *m) {
    printf("%s/n", (char *)gtk_widget_get_name(wid));
    m->command = mx_arrjoin(m->command, "mx_del_user_from_table");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, (char *)gtk_widget_get_name(wid));
    m->command = mx_arrjoin(m->command, "2");
    gtk_widget_hide(wid);
}

static GtkWidget *user_from_bl(char *name, t_main *m) {
    GtkWidget *fix = gtk_fixed_new(); 
    char *markup = g_markup_printf_escaped(MX_NAME_COLOR(m->style->color), name);
    GtkWidget *l = gtk_label_new(NULL);
    GtkWidget *but = gtk_button_new_with_label("Unblock");

    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SLEPT(m->style->color)), 11, 0);
    gtk_label_set_markup(GTK_LABEL(l), markup);
    gtk_fixed_put(GTK_FIXED(fix), resize_image(MX_DEF_PHOTO, 51, 51), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SL_PH(m->style->color)), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), l, 83, 25);
    gtk_fixed_put(GTK_FIXED(fix), but, 210, 21);
    gtk_widget_set_name(but, name);
    g_signal_connect(but, "clicked", G_CALLBACK(mx_unblock_user), m);
    g_idle_add((GSourceFunc)mx_show, fix);
    g_free(markup);
    return fix;
}

void mx_blacklist(t_main *m, t_list *list) {
    int row = 0;

    gtk_widget_destroy(m->grid_user);
    m->grid_user = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_user), 8);
    for (t_list *i = list; i; i = i->next) {
        gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
        gtk_grid_attach(GTK_GRID(m->grid_user), 
            user_from_bl((((t_data *)i->data)->name), m), 0, row++, 1, 1);
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_users), m->grid_user, 0, 8);
    g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
    m->cmd = DEF;
    m->bl = 1;
}
