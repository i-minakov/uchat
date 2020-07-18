#include "uchat.h"

void show_fields(t_wid *wid) {
	gtk_widget_show(wid->log_text);
	gtk_widget_show(wid->log_name);
	gtk_widget_show(wid->log_pas);
	gtk_widget_show(wid->log_but);

	gtk_widget_show(wid->sig_text);
	gtk_widget_show(wid->sig_name);
	gtk_widget_show(wid->sig_pas);
	gtk_widget_show(wid->sig_pas2);
	gtk_widget_show(wid->sig_photo);
	gtk_widget_show(wid->sig_but);
}
