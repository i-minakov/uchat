#include "../inc/uchat.h"

void reset_l_mess(t_user *i) {
    char *s = NULL;
    char *t = NULL;

    if (i->msg->next == NULL) {
        gtk_label_set_text(GTK_LABEL(i->l_mess), "");
        return ;
    }
    t = i->msg->next->text;
    if (t && mx_strlen(t) > 15) {
        s = mx_strpart(t, 14);
        s = mx_delit_fre(s, "...");
        gtk_label_set_text(GTK_LABEL(i->l_mess), s);
        free(s);
    }
    else 
        gtk_label_set_text(GTK_LABEL(i->l_mess), t);
}
