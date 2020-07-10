#include "../inc/uchat.h"

void burger_leave(GtkWidget *widget, GdkEvent *event, t_main *m) {
    gtk_widget_destroy(m->cap->burger_but_img);
<<<<<<< HEAD
    if (m->menu->flag == 1) 
=======
    if (m->menu->flag == 1 || m->set->flag == 1) 
>>>>>>> 07d398e9ae83888db01a1730699de159d91143aa
        m->cap->burger_but_img = gtk_image_new_from_file("./src/resource/cancel.png");
    else
        m->cap->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
}
