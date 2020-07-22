#include "../inc/uchat.h"

static void log_widgets(t_wid *wid) {
	wid->log->log_gif = GTK_WIDGET(gtk_builder_get_object(wid->builder, "loggif"));
	wid->log->log_text = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_text"));
	wid->log->log_name = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_name"));
	wid->log->log_pas = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_pas"));
	wid->log->log_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "log_ok"));
	wid->log->logname = NULL;
}

static void sig_widgets(t_wid *wid) {
	wid->sig->sig_gif = GTK_WIDGET(gtk_builder_get_object(wid->builder, "siggif"));
	wid->sig->sig_text = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_text"));
	wid->sig->sig_name = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_name"));
	wid->sig->sig_pas = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_pas"));
	wid->sig->sig_pas2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_rep_pas"));
	wid->sig->sig_photo = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_photo"));
	wid->sig->flagimg = 0;
	wid->sig->sig_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sig_ok"));
}

static void valid_widgets(t_wid *wid) {
	wid->log->no_fil_log = GTK_WIDGET(gtk_builder_get_object(wid->builder, "required1"));
	wid->sig->no_fil_sig = GTK_WIDGET(gtk_builder_get_object(wid->builder, "required2"));
	// wid->the_end = gtk_image_new_from_file ("./img/2.gif");
	// gtk_fixed_put(wid->fixed, wid->the_end, 0, 0);
	//gtk_widget_hide(wid->the_end);
	wid->sig->sigfile = NULL;

	wid->badact = GTK_WIDGET(gtk_builder_get_object(wid->builder, "bad_img"));
	wid->badact_but = GTK_WIDGET(gtk_builder_get_object(wid->builder, "badbut"));
	wid->black_back = GTK_WIDGET(gtk_builder_get_object(wid->builder, "black_back"));
}

void init_widgets_start(t_wid *wid, t_eye *eye) {
	wid->log->log_hower = GTK_WIDGET(gtk_builder_get_object(wid->builder, "login"));
	wid->sig->sig_hower = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sigin"));
	wid->log->log_hower2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "login1"));
	wid->sig->sig_hower2 = GTK_WIDGET(gtk_builder_get_object(wid->builder, "sigin1"));
	
	log_widgets(wid);
	sig_widgets(wid);
	valid_widgets(wid);

	eye->log = false;
	eye->sig = false;
	eye->sig2 = false;
}
