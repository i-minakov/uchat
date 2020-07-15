#include "../inc/uchat.h"

void b_ic(t_main *m) {
    if (!gtk_widget_is_visible(m->menu->setic)) {
        gtk_widget_show(m->menu->setic);
        gtk_widget_show(m->menu->searchic);
        gtk_widget_show(m->menu->contic);
        gtk_widget_show(m->menu->exic);
    }
    gtk_widget_hide(m->menu->setic2);
    gtk_widget_hide(m->menu->searchic2);
    gtk_widget_hide(m->menu->contic2);
    gtk_widget_hide(m->menu->exic2);
}

void l_ic(t_main *m) {
    gtk_widget_show(m->menu->setic2);
    gtk_widget_show(m->menu->searchic2);
    gtk_widget_show(m->menu->contic2);
    gtk_widget_show(m->menu->exic2);
    gtk_widget_hide(m->menu->setic);
    gtk_widget_hide(m->menu->searchic);
    gtk_widget_hide(m->menu->contic);
    gtk_widget_hide(m->menu->exic);
}

void the_ic(int flag, t_main *m) {
    if (flag == 1)
        b_ic(m);
    else
        l_ic(m);   
}
