#include "../inc/uchat.h"

// void hide_all(t_wid *wid) {
// 	gtk_widget_hide(wid->log->log_gif);
// 	gtk_widget_hide(wid->log->log_text);
// 	gtk_widget_hide(wid->log->log_name);
// 	gtk_widget_hide(wid->log->log_pas);
// 	gtk_widget_hide(wid->log->log_but);

// 	gtk_widget_hide(wid->sig->sig_gif);
// 	gtk_widget_hide(wid->sig->sig_text);
// 	gtk_widget_hide(wid->sig->sig_name);
// 	gtk_widget_hide(wid->sig->sig_pas);
// 	gtk_widget_hide(wid->sig->sig_pas2);
// 	gtk_widget_hide(wid->sig->sig_photo);
// 	gtk_widget_hide(wid->sig->sig_but);
// 	gtk_widget_hide(wid->sig->sig_add_img);
// }

// void win_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid) {
// 	(void)widget;
// 	(void)event;
// 	gtk_widget_show(wid->log->log_hower);
// 	gtk_widget_show(wid->sig->sig_hower);
// 	hide_all(wid);
// }

void init_builder(t_wid *wid) {
	wid->builder = gtk_builder_new();
	gtk_builder_add_from_file (wid->builder, "source/resource/main_hello.glade", NULL);
	wid->window = GTK_WIDGET(gtk_builder_get_object(wid->builder, "main_window"));
	wid->fixed = GTK_WIDGET(gtk_builder_get_object(wid->builder, "fixed"));
	
	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "src/style.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
								GTK_STYLE_PROVIDER(cssProvider),
								GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void do_opening(t_wid *wid) {
	clock_t t;

  	t = clock();
	while(((clock() - t)/CLOCKS_PER_SEC) < 12);
	gtk_widget_hide(wid->start_gif);
	g_idle_remove_by_data(wid);
}

int log_screen(t_main *m)
{
	int ex = 0;
	t_wid *wid = (t_wid *)malloc(sizeof(t_wid) * 10);
	wid->sig = (t_sign *)malloc(sizeof(t_sign) * 16);
	wid->log = (t_login *)malloc(sizeof(t_login) * 10);
	t_eye *eye = (t_eye *)malloc(sizeof(t_eye) * 4);
    eye->wid = wid;
	wid->m = m;
	wid->m->log_in = wid;
	wid->sig->sigfile = NULL;

	gtk_init(NULL, NULL);
	init_builder(wid);
	init_widgets_start(wid, eye);
	init_signals_start(wid, eye);

    // g_object_unref(wid->builder);

    gtk_widget_show(wid->window); 
	//g_idle_add((GSourceFunc)do_opening, wid);

    // gtk_main();
	// free(wid);
    return ex;
}
