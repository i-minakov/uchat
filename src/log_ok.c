#include "../inc/uchat.h"

void log_ok(GtkWidget *widget, t_wid *wid) {
	wid->log->logname = (char *)gtk_entry_get_text (GTK_ENTRY (wid->log->log_name));
	wid->log->logpas = (char *)gtk_entry_get_text (GTK_ENTRY (wid->log->log_pas));
	
	if (mx_strcmp(wid->log->logname, "\0") == 0 || mx_strcmp(wid->log->logpas, "\0") == 0 )
		gtk_widget_show(wid->log->no_fil_log);
	else {
		if(gtk_widget_is_visible (wid->log->no_fil_log))
			gtk_widget_hide (wid->log->no_fil_log);
		sleep(3);
		gtk_widget_destroy(wid->window);
		gtk_main_quit();
	}		
}
