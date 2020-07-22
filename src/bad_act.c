#include "../inc/uchat.h"

static int countpix(char *str) {
	int res = 0;

	for(int i = 0; str[i]; i++) {
		if(i > 64 && i < 91)
			res += 9;
		else if(str[i] == 20 || str[i] == 33 || str[i] == 39 
			|| str[i] == 46 || str[i] == 44 || str[i] == 45 ||
			str[i] == 58 || str[i] == 59 || str[i] == 105 || 
			str[i] == 106 || str[i] == 108)
			res += 4;
		else
			res += 7;
		res++;
	}
	return res;
}

static void seting(t_wid *wid, char *tmp) {
	int marg;

	marg = 300 + ((492 - countpix(tmp))/2);
	mx_printint(countpix(tmp));
	wid->badact_lab = gtk_label_new (tmp);
	gtk_fixed_put(GTK_FIXED(wid->fixed), wid->badact_lab, marg, 350);
	gtk_widget_show(wid->badact_lab);
	g_signal_handlers_block_by_func(wid->sig->sig_gif, log_enter_notify_event, wid);
	g_signal_handlers_block_by_func(wid->log->log_gif, sig_enter_notify_event, wid);
}


static void show_wid(t_wid *wid, int flag, int thred, char *tmp) {
	if (thred == 1) {
		gtk_widget_show(wid->badact);
		gtk_widget_show(wid->badact_but);
		gtk_widget_show(wid->black_back);
		if(wid->sig->flagimg == 1)
			gtk_widget_hide(wid->sig->sig_display);
	}
	else {
		g_idle_add((GSourceFunc)mx_show, wid->badact);
		g_idle_add((GSourceFunc)mx_show, wid->badact_but);
		g_idle_add((GSourceFunc)mx_show, wid->black_back);
		if(wid->sig->flagimg == 1)
			g_idle_add((GSourceFunc)mx_hide, wid->sig->sig_display);
	}
	seting(wid, tmp);
}

void bad_act(t_wid *wid, int flag, int thred) {
	char *tmp = NULL;

	if(flag == 1)
		tmp = "Wrong login or password";
	if(flag == 2)
		tmp = "Login can only contains chars and numbers";
	if(flag == 3)
		tmp = "Passwords mismatch";
	if(flag == 4)
		tmp = "PNG, JPG and JPEG formats acceptable";
	if(flag == 5)
		tmp = "The access to this photo is denied";
	if(flag == 6)
		tmp = "Login must start with letters";
	if(flag == 7)
		tmp = "Password can only contains chars and numbers";
	show_wid(wid, flag, thred, tmp);
}
