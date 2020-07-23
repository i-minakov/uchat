#include "../inc/uchat.h"

void emo_on(GtkWidget *w, t_main *m) {
    if (gtk_widget_is_visible(m->grid_stic)) {
        gtk_widget_hide(m->grid_stic);
        gtk_widget_show(m->grid_emo);
        gtk_widget_set_name(m->stic_smile, "stic2");
        gtk_widget_set_name(m->stic_stic, "stic");
    }
}
