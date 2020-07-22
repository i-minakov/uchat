#include "../inc/uchat.h"

void log_ok(GtkWidget *widget, t_wid *wid) {
	wid->log->logname = (char *)gtk_entry_get_text (GTK_ENTRY (wid->log->log_name));
	wid->log->logpas = (char *)gtk_entry_get_text (GTK_ENTRY (wid->log->log_pas));
	
	if (mx_strcmp(wid->log->logname, "\0") == 0 || mx_strcmp(wid->log->logpas, "\0") == 0 )
		gtk_widget_show(wid->log->no_fil_log);
	else {
		if(gtk_widget_is_visible (wid->log->no_fil_log))
			gtk_widget_hide (wid->log->no_fil_log);
		wid->m->command = mx_arrjoin(wid->m->command, "mx_update");
		wid->m->command = mx_arrjoin(wid->m->command, "user");
		wid->m->command = mx_arrjoin(wid->m->command, wid->log->logname);
		wid->m->cmd = CHECK_PASS;
		// gtk_main_quit();
	}		
}
