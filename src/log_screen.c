#include "../inc/uchat.h"

void hide_all(t_wid *wid) {
	gtk_widget_hide(wid->log_gif);
	gtk_widget_hide(wid->log_text);
	gtk_widget_hide(wid->log_name);
	gtk_widget_hide(wid->log_pas);
	gtk_widget_hide(wid->log_but);

	gtk_widget_hide(wid->sig_gif);
	gtk_widget_hide(wid->sig_text);
	gtk_widget_hide(wid->sig_name);
	gtk_widget_hide(wid->sig_pas);
	gtk_widget_hide(wid->sig_pas2);
	gtk_widget_hide(wid->sig_photo);
	gtk_widget_hide(wid->sig_but);
}

void win_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid) {
	gtk_widget_show(wid->log_hower);
	gtk_widget_show(wid->sig_hower);
	hide_all(wid);
}

///////////////////////////////////////

void init_builder(t_wid *wid) {
	wid->builder = gtk_builder_new();
	gtk_builder_add_from_file (wid->builder, "glade/main_hello.glade", NULL);
	wid->window = GTK_WIDGET(gtk_builder_get_object(wid->builder, "main_window"));
	wid->fixed = GTK_WIDGET(gtk_builder_get_object(wid->builder, "fixed"));
	

	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "css/style.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
								GTK_STYLE_PROVIDER(cssProvider),
								GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int log_screen(void)
{
	int ex = 0;
	t_wid *wid = (t_wid *)malloc(sizeof(t_wid) * 1000);
	t_eye *eye = (t_eye *)malloc(sizeof(t_eye) * 4);
    eye->wid = wid;
	wid->logname = NULL;

	gtk_init(NULL, NULL);
	init_builder(wid);
	init_widgets_start(wid, eye);
	init_signals_start(wid, eye);

    g_object_unref(wid->builder);

    gtk_widget_show(wid->window); 

    gtk_main();
	free(wid);
    return ex;
}
