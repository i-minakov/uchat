#include "../inc/uchat.h"

static void hide_me(t_main *m) {
    gtk_widget_hide(m->menu->menu_box);
    gtk_widget_hide(m->menu->menu_img);
    gtk_widget_hide(m->menu->lang_text);
    gtk_widget_hide(m->menu->color_text);
    gtk_widget_hide(m->menu->lang1);
    gtk_widget_hide(m->menu->lang2);
    gtk_widget_hide(m->menu->color1);
    gtk_widget_hide(m->menu->color2);
    gtk_widget_hide(m->menu->user_search);
    m->menu->flag = 0;
}

static void show_me(t_main *m) {
    gtk_widget_show(m->menu->menu_box);
    gtk_widget_show(m->menu->menu_img);
    gtk_widget_show(m->menu->lang_text);
    gtk_widget_show(m->menu->color_text);
    gtk_widget_show(m->menu->lang1);
    gtk_widget_show(m->menu->lang2);
    gtk_widget_show(m->menu->color1);
    gtk_widget_show(m->menu->color2);
    gtk_widget_show(m->menu->user_search);
    m->menu->flag = 1;  
}

void switch_menu(GtkWidget *wid, t_main *m) {
    char *way = NULL;
    int y;

    if (m->menu->flag == 0) {
        way = "./src/resource/cancel.png";
        y = 42;
        show_me(m);
    }
    else {
        way = "./src/resource/burger2.png";
        y = 37;
        hide_me(m);
    }
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file(way);
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, y);
    gtk_widget_show(m->cap->burger_but_img);
}
