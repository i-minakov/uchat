#include "../inc/uchat.h"

void reply_msg(GtkMenuItem *item, t_msg *msg) {
    (void)item;
    if (msg->text) {
        if (msg->forward != 2) 
           msg->user->m->text = mx_backjoin("Replied at:\n", msg->text);
        else
            msg->user->m->text = msg->text;
        // add_message(msg->user, create_struct(msg->user->m->text, true, 2, NULL), msg->next->id + 1);
    }
    // else 
        // add_file(msg->user->m, (gchar *)msg->filename, true);
}
