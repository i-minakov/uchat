#include "../inc/uchat.h"

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
	gchar *tmp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(wid->sig->sig_photo));
	
	for (int i = 0; tmp[i]; i++) {
		if(tmp[i] == '.') {
			if (mx_strcmp(&tmp[i], ".png") == 0 || mx_strcmp(&tmp[i], ".jpg") == 0
				|| mx_strcmp(&tmp[i], ".jpeg") == 0) {
				wid->sig->sigfile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(wid->sig->sig_photo));
				if(show_photo(wid))
				return ;
				bad_act(wid, 5, 1);
				wid->sig->sigfile = NULL;
			}
		}
	}
	bad_act(wid, 4, 1);
	wid->sig->sigfile = NULL;
}
