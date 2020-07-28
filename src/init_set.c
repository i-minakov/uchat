#include "../inc/uchat.h"

static void put_fix(t_main *m) {
    m->set->my_frame2 = gtk_image_new_from_file("./source/resource/my_fr2.png");
    m->set->my_frame = gtk_image_new_from_file("./source/resource/my_fr1.png");
    m->set->chan_ph = gtk_button_new();
    m->set->flag = 0;
    gtk_widget_set_size_request (m->set->chan_ph, 80, 80);
    gtk_widget_set_opacity (m->set->chan_ph, 0.0);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_photo, 30, 30);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_frame2, 30, 30);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_frame, 30, 30);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->chan_ph, 30, 30);
}

static void secondary_init(t_main *m) {
    m->set->color2 = GTK_WIDGET(gtk_builder_get_object(
            m->builder, "color2"));
    m->set->my_name = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "my_name"));
    m->set->my_pas = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "my_pas"));
    m->set->set_but = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "set_but"));
    m->set->chan_name = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "chan_name"));
    m->set->chan_pas = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "chan_pas"));
    m->set->my_photo = m->set->my_photo = resize_proportion(mx_cooljoin(mx_delit_fre 
        (mx_strjoin("./source/cash_", m->my_name), "/"),  
            mx_strjoin(m->my_name, ".jpg")), 80, 80);
    m->set->my_frame2 = gtk_image_new_from_file
        ("./source/resource/my_fr2.png");
    m->set->my_frame = gtk_image_new_from_file
        ("./source/resource/my_fr1.png");
    m->set->chan_ph = gtk_button_new();
    m->set->flag = 0;
    m->set->notif_flag = 1; 
}

void init_set(t_main *m) {
    m->set->sett_box = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "set_img"));
    m->set->sett_fix = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "setting_bar"));
    m->set->color_text = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Colorlab"));
    m->set->lang_text = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Langlab"));
    m->set->notif_text = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Notiflab"));
    m->set->notif1 = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Not1"));
    m->set->lang1 = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Lang1"));
    m->set->color1 = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "color1"));
     m->set->lang2 = GTK_WIDGET(gtk_builder_get_object
        (m->builder, "Lang2"));
    secondary_init(m);
    put_fix(m);
}
