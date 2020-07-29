#include "../inc/uchat.h"

void show_set(t_main *m) {
    hide_menu(m);
    gtk_widget_show(m->set->sett_fix);
    m->set->flag = 1;  
}

void show_menu(t_main *m) {
    gtk_widget_show(m->menu->menu_fix);
    m->menu->flag = 1;
}

void show_fields(t_wid *wid) {
	gtk_widget_show(wid->log->log_text);
	gtk_widget_show(wid->log->log_name);
	gtk_widget_show(wid->log->log_pas);
	gtk_widget_show(wid->log->log_but);

	gtk_widget_show(wid->sig->sig_text);
	gtk_widget_show(wid->sig->sig_name);
	gtk_widget_show(wid->sig->sig_pas);
	gtk_widget_show(wid->sig->sig_pas2);
	gtk_widget_show(wid->sig->sig_photo);
	gtk_widget_show(wid->sig->sig_but);
	gtk_widget_show(wid->sig->sig_add_img);
}
