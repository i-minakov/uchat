#include "../inc/uchat.h"

static bool show_photo (t_wid *wid) {
	GtkWidget *tmp = resize_image_correct(wid->sigfile);

	if (tmp == NULL)
		return false;
	if(wid->flagimg == 1)
		gtk_widget_destroy(wid->sig_display);
	wid->sig_display = tmp;
	gtk_fixed_put(GTK_FIXED(wid->fixed), wid->sig_display, 0, 0);
	gtk_widget_show(wid->sig_display);
	wid->flagimg = 1;
	return true;
}

void add_sig_photo(GtkWidget *widget, t_wid *wid) {
	gchar *tmp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(wid->sig_photo));
	
	for (int i = 0; tmp[i]; i++) {
		if(tmp[i] == '.') {
			if (strcmp(&tmp[i], ".png") == 0 || strcmp(&tmp[i], ".jpg") == 0
				|| strcmp(&tmp[i], ".gif") == 0 || strcmp(&tmp[i], ".svg") == 0) {
				wid->sigfile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(wid->sig_photo));
				if(show_photo (wid))
				return ;
				bad_act(wid, 5);
				wid->sigfile = NULL;
			}
		}
	}
	bad_act(wid, 4);
	wid->sigfile = NULL;
}
