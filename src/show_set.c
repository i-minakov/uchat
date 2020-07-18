#include "uchat.h"

void show_set(t_main *m) {
    hide_menu(m);
    gtk_widget_show(m->set->sett_fix);
    // gtk_widget_show(m->set->sett_box);
    // gtk_widget_show(m->set->sett_fix);
    // gtk_widget_show(m->set->lang_text);
    // gtk_widget_show(m->set->color_text);
    // gtk_widget_show(m->set->lang1);
    // gtk_widget_show(m->set->lang2);
    // gtk_widget_show(m->set->color1);
    // gtk_widget_show(m->set->color2);
    // gtk_widget_show(m->set->my_name);
    // gtk_widget_show(m->set->set_but);
    // gtk_widget_show(m->set->my_photo);
    // gtk_widget_show(m->set->my_frame);
    m->set->flag = 1;  
}
