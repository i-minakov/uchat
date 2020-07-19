#include "uchat.h"

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
}
