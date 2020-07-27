#include "../inc/uchat.h"

void hide_set(t_main *m) {
    hide_menu(m);
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file("./source/resource/burger.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
    gtk_widget_hide(m->set->sett_fix);
    m->set->flag = 0; 
}
