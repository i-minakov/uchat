#include "../inc/uchat.h"

static void edit_done(GtkEntry *e, t_msg *msg) {
    char *str = NULL;
    int k = 0;
    GtkWidget *dialog;
    GtkDialogFlags flags;

    mx_strdel(&msg->text);
    msg->text = mx_strdup((char *)gtk_entry_get_text(GTK_ENTRY(msg->user->m->edit_entry)));
    str = mx_strnew(mx_strlen(msg->text) + ((mx_strlen(msg->text)/50) + 1));
    for (int j = 0; msg->text[j]; j++) {
        str[k++] = msg->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    gtk_button_set_label(GTK_BUTTON(msg->label), str);
    gtk_widget_hide(msg->user->m->edit_entry);
    gtk_widget_show(msg->user->m->sms);
    free(str);
    // if (msg->text == NULL || !mx_strlen(msg->text)) {
    //     flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    //     dialog = gtk_dialog_new_with_buttons ("Delete message?", GTK_WINDOW(msg->user->m->window),
    //         flags, ("_Yes"), GTK_RESPONSE_ACCEPT, ("_No"), GTK_RESPONSE_REJECT, NULL);
    //     if ((gtk_dialog_run(GTK_DIALOG (dialog))) == GTK_RESPONSE_ACCEPT)
    //         delete_msg(NULL, msg);
    //     gtk_widget_destroy (dialog);
    // }
}

void edit_msg(GtkMenuItem *item, t_msg *msg) {
    // GtkWidget *lab = gtk_label_new(NULL);
    // char *markup = g_markup_printf_escaped(
    //         "<span color=\"white\" font=\"12\"> Editing: %s</span>", msg->text);

    // gtk_label_set_markup(GTK_LABEL(lab), markup); 
    // gtk_fixed_put(GTK_FIXED(msg->user->m->fix1), lab, 364, 610);
    // gtk_widget_show(lab);
    // g_free(markup);
    gtk_widget_hide(msg->user->m->sms);
    gtk_widget_show(msg->user->m->edit_entry);
    gtk_entry_set_text(GTK_ENTRY(msg->user->m->edit_entry), msg->text);
    g_signal_connect(msg->user->m->edit_entry, "activate", G_CALLBACK(edit_done), msg);
}
