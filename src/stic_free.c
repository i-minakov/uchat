#include "../inc/uchat.h"

void stic_free(t_main *m) {
    free(m->stic->img);
    free(m->stic->but);
    mx_del_strarr(&m->stic->way);
    free(m->emo->img);
    free(m->emo->but);
    mx_del_strarr(&m->emo->utf);
}
