#include "../inc/uchat.h"

void attach_file(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    gchar *tmp = NULL;

    if (icon_pos == GTK_ENTRY_ICON_SECONDARY)
        return ;
    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
        if (entry != NULL)
        add_file(m, tmp, true);
        else 
            puts("++++\n");
    }
    gtk_widget_destroy (dialog);
}
