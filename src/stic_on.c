#include "../inc/uchat.h"

void stic_free(t_main *m) {
    free(m->stic->img);
    free(m->stic->but);
    mx_del_strarr(&m->stic->way);
    free(m->emo->img);
    free(m->emo->but);
    mx_del_strarr(&m->emo->utf);
}

void stic_on(GtkWidget *w, t_main *m) {
    (void)w;
    if (gtk_widget_is_visible(m->grid_emo)) {
        gtk_widget_hide(m->grid_emo);
        gtk_widget_show(m->grid_stic);
        gtk_widget_set_name(m->stic_smile, "stic");
        gtk_widget_set_name(m->stic_stic, "stic2");
    }
}
