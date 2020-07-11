#include "../inc/uchat.h"

void hide_start(t_wid *wid) {
	if(gtk_widget_is_visible (wid->log_hower))
		gtk_widget_hide(wid->log_hower);
	if(gtk_widget_is_visible (wid->sig_hower))
		gtk_widget_hide(wid->sig_hower);
	if(gtk_widget_is_visible (wid->log_hower2))
		gtk_widget_hide(wid->log_hower2);
	if(gtk_widget_is_visible (wid->sig_hower2))
		gtk_widget_hide(wid->sig_hower2);	
}
