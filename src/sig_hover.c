#include "uchat.h"

void sig_hover(GtkWidget *widget, GdkEventButton *event, t_wid *wid)
{
	if(gtk_widget_is_visible (wid->sig->sig_hower2)) {
		gtk_widget_hide(wid->sig->sig_hower2);
		gtk_widget_show(wid->sig->sig_hower);
		gtk_widget_hide(wid->log->log_hower2);
		gtk_widget_show(wid->log->log_hower);
	}
}
