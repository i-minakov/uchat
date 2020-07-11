
#include "../inc/uchat.h"

static void seting(t_wid *wid, char *tmp) {
	int marg;

	marg = 300 + ((492 - strlen(tmp))/2);
	gtk_label_set_label(GTK_LABEL(wid->badact_lab), tmp);
	gtk_label_set_xalign(GTK_LABEL(wid->badact_lab), marg);
	g_signal_handlers_block_by_func(wid->sig_gif, log_enter_notify_event, wid);
	g_signal_handlers_block_by_func(wid->log_gif, sig_enter_notify_event, wid);
	if(wid->flagimg == 1)
		gtk_widget_hide(wid->sig_display);
}

void bad_act(t_wid *wid, int flag) {
	char *tmp = NULL;
	int marg;

	gtk_widget_show(wid->badact);
	gtk_widget_show(wid->badact_but);
	gtk_widget_show(wid->badact_lab);
	gtk_widget_show(wid->black_back);
	if(flag == 1)
		tmp = "Wrong login or password";
	if(flag == 2)
		tmp = "Login can only contains chars and numbers";
	if(flag == 3)
		tmp = "Passwords mismatch";
	if(flag == 4)
		tmp = "You can attach file only in PNG, JPEG, SVG and GIF format";
	if(flag == 5)
		tmp = "The access to this photo is denied";
	seting(wid, tmp);
}
