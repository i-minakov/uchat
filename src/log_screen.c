#include "../inc/uchat.h"

void init_builder(t_wid *wid) {
	wid->builder = gtk_builder_new();
	gtk_builder_add_from_file (wid->builder, "source/resource/main_hello.glade", NULL);
	wid->window = GTK_WIDGET(gtk_builder_get_object(wid->builder, "main_window"));
	wid->fixed = GTK_WIDGET(gtk_builder_get_object(wid->builder, "fixed"));
	
	if (wid->start_flag  == 1) {
		wid->cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_path(wid->cssProvider, "./src/unset.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(wid->cssProvider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
		wid->start_flag = 0;
	}
	wid->cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(wid->cssProvider, "src/style.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
								GTK_STYLE_PROVIDER(wid->cssProvider),
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
	t_wid *wid = m->log_in;
	t_eye *eye = (t_eye *)malloc(sizeof(t_eye) * 4);
    eye->wid = wid;

	gtk_init(NULL, NULL);
	init_builder(wid);
	init_widgets_start(wid, eye);
	init_signals_start(wid, eye);
    gtk_widget_show(wid->window); 
    return ex;
}
