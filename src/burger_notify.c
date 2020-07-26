#include "../inc/uchat.h"

void burger_notify(GtkWidget *widget, GdkEvent *event, t_main *m) {
    int y;

    (void)widget;
    (void)event;
    gtk_widget_destroy(m->cap->burger_but_img);
    if (m->menu->flag == 1 || m->set->flag == 1) {
        m->cap->burger_but_img = gtk_image_new_from_file("./source/resource/canselhover.png");
        y = 45;
    }
    else {
        m->cap->burger_but_img = gtk_image_new_from_file("./source/resource/burger2.png");
        y = 37;
    }
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, y);
    gtk_widget_show(m->cap->burger_but_img);
}
