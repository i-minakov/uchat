#include "../inc/uchat.h"

static bool sigcheck(gchar *login) {
	for(int i = 0; login[i]; i++) {
		if(login[i] < 48 || (login[i] > 57 && login[i] < 65) 
			|| (login[i] > 90 && login[i] < 97) || login[i] > 122)
			return false;
	}
	return true;
}

static bool valid(t_wid *wid) {
	int f = 0;

	if(gtk_widget_is_visible(wid->sig->no_fil_sig))
			gtk_widget_hide(wid->sig->no_fil_sig);
	if (mx_isdigit(wid->sig->signame[0]))
			f = 6;
	if (!sigcheck(wid->sig->signame))
			f = 2;
	if (!sigcheck(wid->sig->sigpas))
			f = 7;
	if (mx_strcmp(wid->sig->sigpas, wid->sig->sigpas2) != 0)
			f = 3;
	if (f != 0){
		bad_act(wid, f, 1);
		return false;
	}
		return true;
}

void sig_ok(GtkWidget *widget, t_wid *wid) {
	(void)widget;
  	wid->sig->signame = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig->sig_name));
	wid->sig->sigpas = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig->sig_pas));
	wid->sig->sigpas2 = (char *)gtk_entry_get_text (GTK_ENTRY (wid->sig->sig_pas2));

	if (mx_strcmp(wid->sig->signame, "\0") == 0 || mx_strcmp(wid->sig->sigpas, "\0") == 0 ||
		mx_strcmp(wid->sig->sigpas2, "\0") == 0)
		gtk_widget_show(wid->sig->no_fil_sig);
	else {
		if (valid(wid)){
			wid->m->command = mx_arrjoin(wid->m->command, "mx_update");
			wid->m->command = mx_arrjoin(wid->m->command, "user");
			wid->m->command = mx_arrjoin(wid->m->command, wid->sig->signame);
			gtk_widget_hide(wid->sig->sig_but);
			gtk_widget_show(wid->wait_gif);
			wid->m->cmd = CHECK_US;
		}
	}
}
