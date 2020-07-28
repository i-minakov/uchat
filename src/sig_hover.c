#include "../inc/uchat.h"

void sig_hover(GtkWidget *widget, GdkEventButton *event, t_wid *wid) {
	(void)widget;
	(void)event;
	if(gtk_widget_is_visible (wid->sig->sig_hower_pic2)) {
		gtk_widget_hide(wid->sig->sig_hower_pic2);
		gtk_widget_show(wid->sig->sig_hower_pic1);
		gtk_widget_hide(wid->log->log_hower_pic2);
		gtk_widget_show(wid->log->log_hower_pic1);
	}
}
