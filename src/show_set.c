#include "../inc/uchat.h"

void show_set(t_main *m) {
    hide_menu(m);
    gtk_widget_show(m->set->sett_fix);
    m->set->flag = 1;  
}
