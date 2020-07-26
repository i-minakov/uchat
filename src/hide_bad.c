#include "../inc/uchat.h"

void hide_bad(GtkWidget *widget, t_wid *wid) {
	(void)widget;
	gtk_widget_hide(wid->badact_but);
	gtk_widget_destroy(wid->badact_lab);
	gtk_widget_hide(wid->badact);
	gtk_widget_hide(wid->black_back);
	g_signal_handlers_unblock_by_func((void *)wid->sig->sig_gif,
		(void *)log_enter_notify_event, (void *)wid);
	g_signal_handlers_unblock_by_func((void *)wid->log->log_gif,
		(void *)sig_enter_notify_event, (void *)wid);
	if(wid->sig->flagimg == 1)
		gtk_widget_show(wid->sig->sig_display);
}
