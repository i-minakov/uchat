#include "../inc/uchat.h"

static void stic_and_fix(t_main *m) {
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->contic, 40, 35);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->contic2, 40, 35);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->setic, 40, 75);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->setic2, 40, 75);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->searchic, 40, 115);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->searchic2, 40, 115);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->blackic, 40, 153);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->blackic2, 40, 153);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->exic, 40, 195);
    gtk_fixed_put(GTK_FIXED(m->menu->menu_fix), m->menu->exic2, 40, 195);
    m->fix_for_stic = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_fix"));
    m->stic_fix_img = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_img"));
    m->stic_scrol = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_fix_glob"));
    set_stics(m);
}

void init_menu(t_main *m) {
    m->style->color = 1;
    m->style->lang = 1;
    m->menu->menu_box = GTK_WIDGET(gtk_builder_get_object(m->builder, "menu_img"));
    m->menu->menu_fix = GTK_WIDGET(gtk_builder_get_object(m->builder, "menu_box"));
    m->menu->search = GTK_WIDGET(gtk_builder_get_object(m->builder, "search"));
    m->menu->settings = GTK_WIDGET(gtk_builder_get_object(m->builder, "setting"));
    m->menu->contacts = GTK_WIDGET(gtk_builder_get_object(m->builder, "contacts"));
    m->menu->exit = GTK_WIDGET(gtk_builder_get_object(m->builder, "exit"));
    m->menu->black_list = GTK_WIDGET(gtk_builder_get_object(m->builder, "blacklist"));
    m->menu->flag = 0;
    m->menu->setic = gtk_image_new_from_file("./src/resource/setic.png"); 
    m->menu->setic2 = gtk_image_new_from_file("./src/resource/setic2.png"); 
    m->menu->searchic = gtk_image_new_from_file("./src/resource/searchic.png"); 
    m->menu->searchic2 = gtk_image_new_from_file("./src/resource/searchic2.png"); 
    m->menu->exic = gtk_image_new_from_file("./src/resource/exic.png"); ;
    m->menu->exic2 = gtk_image_new_from_file("./src/resource/exic2.png"); ;
    m->menu->contic = gtk_image_new_from_file("./src/resource/contic.png");
    m->menu->contic2 = gtk_image_new_from_file("./src/resource/contic2.png");
    m->menu->blackic = gtk_image_new_from_file("./src/resource/blackic.png");
    m->menu->blackic2 = gtk_image_new_from_file("./src/resource/blackic2.png");
    stic_and_fix(m);
}
