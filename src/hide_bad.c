#include "../inc/uchat.h"

void hide_bad(GtkWidget *widget, t_wid *wid) {
	gtk_widget_hide(wid->badact_but);
	gtk_widget_hide(wid->badact_lab);
	gtk_widget_hide(wid->badact);
	gtk_widget_hide(wid->black_back);
	g_signal_handlers_unblock_by_func(wid->sig_gif, log_enter_notify_event, wid);
	g_signal_handlers_unblock_by_func(wid->log_gif, sig_enter_notify_event, wid);
	if(wid->flagimg == 1)
		gtk_widget_show(wid->sig_display);
}
