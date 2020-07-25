#include "../inc/uchat.h"


gchar *make_chooser(t_wid *wid) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    gchar *tmp = NULL;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(wid->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
    }
    gtk_widget_destroy (dialog);
	return tmp;
}

static bool show_photo (t_wid *wid) {
	GtkWidget *tmp = resize_image_correct(wid->sig->sigfile);

	if (tmp == NULL)
		return false;
	if(wid->sig->flagimg == 1)
		gtk_widget_destroy(wid->sig->sig_display);
	wid->sig->sig_display = tmp;
	gtk_fixed_put(GTK_FIXED(wid->fixed), wid->sig->sig_display, 0, 0);
	gtk_widget_show(wid->sig->sig_display);
	wid->sig->flagimg = 1;
	return true; 
}

void add_sig_photo(GtkWidget *widget, t_wid *wid) {
	gchar *tmp = make_chooser(wid);
	// puts(tmp);
	for (int i = 0; tmp[i]; i++) {
		if(tmp[i] == '.') {
			if (mx_strcmp(&tmp[i], ".png") == 0 || mx_strcmp(&tmp[i], ".jpg") == 0
				|| mx_strcmp(&tmp[i], ".jpeg") == 0) {
				wid->sig->sigfile = tmp;
				if(show_photo(wid))
				return ;
				bad_act(wid, 5, 1);
				wid->sig->sigfile = NULL;
				return ;
			}
		}
	}
	bad_act(wid, 4, 1);
	wid->sig->sigfile = NULL;
}
