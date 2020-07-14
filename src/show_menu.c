#include "../inc/uchat.h"

void show_menu(t_main *m) {
    gtk_widget_show(m->menu->menu_box);
    gtk_widget_show(m->menu->search);
    gtk_widget_show(m->menu->settings);
    gtk_widget_show(m->menu->contacts);
    gtk_widget_show(m->menu->exit);
    m->menu->flag = 1;
}
