#include "../inc/uchat.h"

void log_ok(GtkWidget *widget, t_wid *wid) {
	wid->logname = gtk_entry_get_text (GTK_ENTRY (wid->log_name));
	wid->logpas = gtk_entry_get_text (GTK_ENTRY (wid->log_pas));
	
	if (strcmp(wid->logname, "\0") == 0 || strcmp(wid->logpas, "\0") == 0 )
		gtk_widget_show(wid->no_fil_log);
	else {
		if(gtk_widget_is_visible (wid->no_fil_log))
			gtk_widget_hide (wid->no_fil_log);
		// puts(wid->logname);
		// puts(wid->logpas);
		gtk_widget_show(wid->the_end);
		sleep(3);
		gtk_main_quit();
	}		
}
