#include "../inc/uchat.h"

void sign_click(GtkWidget *widget, t_wid *wid) {
	(void)widget;
	hide_start(wid);
	gtk_widget_show(wid->sig->sig_gif_pic);
	gtk_widget_show(wid->sig->sig_gif);
	show_fields(wid);
}
