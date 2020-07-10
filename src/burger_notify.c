#include "../inc/uchat.h"

void burger_notify(GtkWidget *widget, GdkEvent *event, t_main *m) {
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file("./src/resource/burger2.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 37);
    gtk_widget_show(m->cap->burger_but_img);
}
