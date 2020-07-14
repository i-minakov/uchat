#include "../inc/uchat.h"

void hide_menu(t_main *m) {
    gtk_widget_hide(m->menu->menu_box);
    gtk_widget_hide(m->menu->settings);
    gtk_widget_hide(m->menu->search);
    gtk_widget_hide(m->menu->contacts);
    gtk_widget_hide(m->menu->exit);
    m->menu->flag = 0;
}
