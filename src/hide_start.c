#include "../inc/uchat.h"

void hide_start(t_wid *wid) {
	if(gtk_widget_is_visible (wid->log->log_hower))
		gtk_widget_hide(wid->log->log_hower);
	if(gtk_widget_is_visible (wid->log->log_hower_pic1))
		gtk_widget_hide(wid->log->log_hower_pic1);
	if(gtk_widget_is_visible (wid->log->log_hower_pic2))
		gtk_widget_hide(wid->log->log_hower_pic2);

	if(gtk_widget_is_visible (wid->sig->sig_hower))
		gtk_widget_hide(wid->sig->sig_hower);
	if(gtk_widget_is_visible (wid->sig->sig_hower_pic1))
		gtk_widget_hide(wid->sig->sig_hower_pic1);	
		if(gtk_widget_is_visible (wid->sig->sig_hower_pic2))
		gtk_widget_hide(wid->sig->sig_hower_pic2);
}
