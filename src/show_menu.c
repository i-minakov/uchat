#include "../inc/uchat.h"

void show_menu(t_main *m) {
    gtk_widget_show(m->menu->menu_fix);
    m->menu->flag = 1;
}
