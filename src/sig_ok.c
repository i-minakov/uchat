#include "../inc/uchat.h"

static bool sigcheck(gchar *login) {
	for(int i = 0; login[i]; i++) {
		if(login[i] < 48 || (login[i] > 57 && login[i] < 97)
			|| login[i] > 122)
			return false;
	}
	return true;
}

bool valid(t_wid *wid) {
	int f = 0;

	if(gtk_widget_is_visible(wid->no_fil_sig))
			gtk_widget_hide(wid->no_fil_sig);
	if (mx_isdigit(wid->signame[0]))
			f = 6;
	if (!sigcheck(wid->signame))
			f = 2;
	if (!sigcheck(wid->sigpas))
			f = 7;
	if (strcmp(wid->sigpas, wid->sigpas2) != 0)
			f = 3;
	if (f != 0){
		bad_act(wid, f);
		return false;
	}
		return true;
}

void sig_ok(GtkWidget *widget, t_wid *wid) {
  	wid->signame = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig_name));
	wid->sigpas = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig_pas));
	wid->sigpas2 = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig_pas2));

	if (strcmp(wid->signame, "\0") == 0 || strcmp(wid->sigpas, "\0") == 0 ||
		strcmp(wid->sigpas2, "\0") == 0)
		gtk_widget_show(wid->no_fil_sig);
	else {
		if (valid(wid)){
			gtk_widget_show(wid->the_end);
			sleep(3);
			gtk_main_quit();
		}
	}
}
