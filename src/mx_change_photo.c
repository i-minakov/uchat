#include "../inc/header.h"

/* change my photo */
void mx_reset_my_photo(char *path, t_main *m) {
    gtk_widget_destroy(m->cap->my_photo);
    m->cap->my_photo = resize_proportion(path, 51, 51);
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->my_photo, 23, 20);
    gtk_widget_show(m->cap->my_photo);
    gtk_widget_destroy(m->set->my_photo);
    m->set->my_photo = resize_proportion(path, 80, 80);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_photo, 30, 30);
    gtk_widget_show(m->set->my_photo);
}

void mx_change_my_photo(GtkWidget *w, t_main *m) {
    (void)w;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gchar *tmp = NULL;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename(chooser);
        mx_reset_my_photo((char *)tmp, m);
        m->command = mx_arrjoin(m->command, "mx_change_img");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, (char *)tmp);
    }
    gtk_widget_destroy(dialog);
}
