#include "uchat.h"

void log_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid)
{	
	if(gtk_widget_is_visible (wid->sig_gif))
		gtk_widget_hide(wid->sig_gif);
	if (wid->flagimg == 1)
		gtk_widget_hide(wid->sig_display);
	gtk_widget_show(wid->log_gif);
}
