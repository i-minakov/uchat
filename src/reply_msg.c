#include "../inc/uchat.h"

void reply_msg(GtkMenuItem *item, t_msg *msg) {
    t_add_m *s = create_struct(NULL, true, 2, NULL);

    (void)item;
    if (msg->text) {
        if (msg->forward != 2) 
           s->text = mx_backjoin("Replied at:\n", msg->text);
        else
            s->text = mx_strdup(msg->text);
        add_message(msg->user, s, mx_atoi(msg->user->exist_id->data) + 1);
    }
    else {
        s->text = mx_strdup(msg->filename);
        add_file(msg->user, s, msg->stic, mx_atoi(msg->user->exist_id->data) + 1);
    }
    mx_strdel(&s->text);
    free(s);
}
