#include "../inc/uchat.h"

static bool sigcheck(const gchar *login) {
	for(int i = 0; login[i]; i++) {
		if((login[i] < 48 || (login[i] > 57 && login[i] < 97)) 
			&& login[i] > 122)
			return false;
	}
	return true;
}

void sig_ok(GtkWidget *widget, t_wid *wid) {
  	wid->signame = gtk_entry_get_text (GTK_ENTRY (wid->sig_name));
	wid->sigpas = gtk_entry_get_text (GTK_ENTRY (wid->sig_pas));
	wid->sigpas2 = gtk_entry_get_text (GTK_ENTRY (wid->sig_pas2));

	if (strcmp(wid->signame, "\0") == 0 || strcmp(wid->sigpas, "\0") == 0 ||
		strcmp(wid->sigpas2, "\0") == 0)
		gtk_widget_show(wid->no_fil_sig);
	else {
		if(gtk_widget_is_visible(wid->no_fil_sig))
			gtk_widget_hide(wid->no_fil_sig);
		if (!sigcheck(wid->signame))
			bad_act(wid, 2);
		if (strcmp(wid->sigpas, wid->sigpas2) != 0)
			bad_act(wid, 3);
		else {
		gtk_widget_show(wid->the_end);
		sleep(3);
		gtk_main_quit();
		}
	}
}
