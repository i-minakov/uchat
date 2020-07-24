#include "../inc/uchat.h"

void set_emo_tab(t_main *m) {
    m->fix_for_stic = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_fix"));
    m->stic_fix_img = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_img"));
    m->stic_scrol = GTK_WIDGET(gtk_builder_get_object(m->builder, "stic_fix_glob"));
    m->stic_smile = gtk_button_new_with_label ("Emoji");
    m->stic_stic = gtk_button_new_with_label ("Stickers");
    m->stic_line = gtk_image_new_from_file("./source/resource/sticstic.png");

    gtk_fixed_put(GTK_FIXED(m->fix_for_stic), m->stic_smile, 12, 10);
    gtk_fixed_put(GTK_FIXED(m->fix_for_stic), m->stic_stic, 100, 10);
    gtk_fixed_put(GTK_FIXED(m->fix_for_stic), m->stic_line, 90, 15);
    g_signal_connect( m->stic_smile, "clicked", G_CALLBACK(emo_on), m); 
    g_signal_connect( m->stic_stic, "clicked", G_CALLBACK(stic_on), m); 
    gtk_widget_show(m->stic_smile);
    gtk_widget_show(m->stic_stic);
    gtk_widget_show(m->stic_line);
    gtk_widget_set_name(m->stic_smile, "stic2");
    gtk_widget_set_name(m->stic_stic, "stic");
    set_emoji(m);
    set_stics(m);
}
