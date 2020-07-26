#include "../inc/uchat.h"

void sig_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid) {
	(void)widget;
	(void)event;
	if(gtk_widget_is_visible (wid->log->log_gif))
		gtk_widget_hide(wid->log->log_gif);
	gtk_widget_show(wid->sig->sig_gif);
	if (wid->sig->flagimg == 1)
		gtk_widget_show(wid->sig->sig_display);
}
