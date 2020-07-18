#include "uchat.h"

void log_hover(GtkWidget *widget, GdkEventButton *event, t_wid *wid)
{	
	if(gtk_widget_is_visible (wid->log_hower)) {
		gtk_widget_hide(wid->log_hower);
		gtk_widget_show(wid->log_hower2);
		gtk_widget_hide(wid->sig_hower);
		gtk_widget_show(wid->sig_hower2);
	}
}
