#include "../inc/uchat.h"

void hide_menu(t_main *m) {
    gtk_widget_hide(m->menu->menu_fix);
    m->menu->flag = 0;
}
