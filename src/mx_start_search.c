#include "../inc/header.h"


void show_search_msg(GtkWidget *w, t_main *m) {
    (void)w;
    m->flag_search = 1;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    gtk_widget_show(m->search);
}

void show_search_users(GtkWidget *w, t_main *m) {
    (void)w;
    m->flag_search = 2;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    hide_menu(m);
    gtk_widget_show(m->search);
}

void show_search_contacts(GtkWidget *w, t_main *m) {
    (void)w;
    m->flag_search = 3;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    hide_menu(m);
    gtk_widget_show(m->search);
}
