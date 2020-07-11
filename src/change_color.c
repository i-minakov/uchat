#include "../inc/uchat.h"

void wid_change (GtkWidget *widget, GtkWidget *fix, char *way, int x, int y) {
    gtk_widget_destroy(widget);
    widget = gtk_image_new_from_file(way);
    gtk_fixed_put(GTK_FIXED(fix), widget, x, y);
    gtk_widget_show(widget);
}

void change_color(GtkToggleButton *togglebutton, t_main *m) {
    if (m->style->color == 1) {
        m->style->color = 2;
        connect_css(m);
        wid_change(m->bottom_b, m->fix1, "./src/resource/bottom1.png", 327, 610);
        wid_change(m->top_b, m->cap->fix_cap, "./src/resource/top1.png", 0, 0);
    }
}


// m->fix_for_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_text"));
//     m->fix_for_users = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_user"));
//     m->cap->fix_cap = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_cap"));
//     m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
//     m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
//     m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));
//     m->lab_start = GTK_WIDGET(gtk_builder_get_object(m->builder, "lab_start"));
//     m->cap->burger_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "burger_but"));
//     m->cap->dot_menu_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
//     m->scrol_bar = GTK_WIDGET(gtk_builder_get_object(m->builder, "scrol_text"));
//     m->edit_entry = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_edit"));
//     m->file_ch = GTK_WIDGET(gtk_builder_get_object(m->builder, "file_chooser"));
//     m->adj = gtk_adjustment_new(1.0, 1.0, 10000.0, 1.0, 10.0, 1.0);
//     gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(m->scrol_bar), m->adj);