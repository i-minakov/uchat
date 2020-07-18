#include "uchat.h"

void sig_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid)
{
	if(gtk_widget_is_visible (wid->log_gif))
		gtk_widget_hide(wid->log_gif);
	gtk_widget_show(wid->sig_gif);
	if (wid->flagimg == 1)
		gtk_widget_show(wid->sig_display);
}
