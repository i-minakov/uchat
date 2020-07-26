#include "../inc/uchat.h"

static void command_edit(t_main *m, t_msg *msg) {
    char *id = mx_itoa(msg->id);

    m->command = mx_arrjoin(m->command, "mx_edit");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, msg->user->name);
    m->command = mx_arrjoin(m->command, msg->text);
    m->command = mx_arrjoin(m->command, id);
    mx_strdel(&id);
}

static void dialog_delete(t_msg *msg) {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    
    dialog = gtk_dialog_new_with_buttons ("Delete message?", GTK_WINDOW(msg->user->m->window),
        flags, ("_Yes"), GTK_RESPONSE_ACCEPT, ("_No"), GTK_RESPONSE_REJECT, NULL);
    if ((gtk_dialog_run(GTK_DIALOG (dialog))) == GTK_RESPONSE_ACCEPT)
        delete_msg(NULL, msg);
    gtk_widget_destroy (dialog);
}

static void edit_done(GtkEntry *e, t_msg *msg) {
    char *str = NULL;
    int k = 0;

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
    if (msg->text == NULL || !mx_strlen(msg->text))
        dialog_delete(msg);
    else 
        command_edit(msg->user->m, msg);
    free(str);
    g_signal_handlers_disconnect_by_func((void *)e, (void *)edit_done, (void *)msg);
}

void edit_msg(GtkMenuItem *item, t_msg *msg) {
    (void)item;
    gtk_widget_hide(msg->user->m->sms);
    gtk_widget_show(msg->user->m->edit_entry);
    gtk_entry_set_text(GTK_ENTRY(msg->user->m->edit_entry), msg->text);
    g_signal_connect(msg->user->m->edit_entry, "activate", G_CALLBACK(edit_done), msg);
}
