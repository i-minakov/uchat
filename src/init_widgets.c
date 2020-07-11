#include "../inc/uchat.h"

static void log_widgets(t_wid *wid) {
	wid->log_gif = GTK_WIDGET(gtk_builder_get_object(wid->builder, "loggif"));
	wid->log_text = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_text"));
	wid->log_name = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_name"));
	wid->log_pas = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_pas"));
	wid->log_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_ok"));
}

static void sig_widgets(t_wid *wid) {
	wid->sig_gif = GTK_WIDGET(gtk_builder_get_object(wid->builder, "siggif"));
	wid->sig_text = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_text"));
	wid->sig_name = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_name"));
	wid->sig_pas = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_pas"));
	wid->sig_pas2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_rep_pas"));
	wid->sig_photo = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_photo"));
	wid->flagimg = 0;
	wid->sig_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_ok"));
}

static void valid_widgets(t_wid *wid) {
	wid->no_fil_log = GTK_WIDGET(gtk_builder_get_object(wid->builder, "required1"));
	wid->no_fil_sig = GTK_WIDGET(gtk_builder_get_object(wid->builder, "required2"));
	wid->the_end = GTK_WIDGET(gtk_builder_get_object(wid->builder, "the_end"));
	wid->sigfile = NULL;

	wid->badact = GTK_WIDGET(gtk_builder_get_object(wid->builder, "bad_img"));
	wid->badact_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "badbut"));
	wid->badact_lab = GTK_WIDGET(gtk_builder_get_object(wid->builder, "badlab"));
	wid->black_back = GTK_WIDGET(gtk_builder_get_object(wid->builder, "black_back"));
}

void init_widgets_start(t_wid *wid, t_eye *eye) {
	wid->log_hower = GTK_WIDGET(gtk_builder_get_object(wid->builder, "login"));
	wid->sig_hower = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sigin"));
	wid->log_hower2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "login1"));
	wid->sig_hower2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sigin1"));
	
	log_widgets(wid);
	sig_widgets(wid);
	valid_widgets(wid);

	eye->log = false;
	eye->sig = false;
	eye->sig2 = false;
}
