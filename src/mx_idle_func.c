#include "../inc/header.h"

void mx_destroy(GtkWidget *wid) {
    gtk_widget_destroy(wid);
    g_idle_remove_by_data(wid);
}

void mx_show(GtkWidget *wid) {
    gtk_widget_show_all(wid);
    g_idle_remove_by_data(wid);
}

void mx_hide(GtkWidget *w) {
    gtk_widget_hide(w);
    g_idle_remove_by_data(w);
}

void mx_idle_destroy(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_destroy(wid);
    else 
        g_idle_add((GSourceFunc)mx_show, wid);
}

void mx_idle_show(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_show_all(wid);
    else 
        g_idle_add((GSourceFunc)mx_show, wid);
}

void mx_idle_hide(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_hide(wid);
    else 
        g_idle_add((GSourceFunc)mx_hide, wid);
}
