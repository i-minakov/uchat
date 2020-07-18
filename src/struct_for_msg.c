#include "uchat.h"

t_add_m *create_struct(char *text, bool my, int forw, char *time_m) {
    t_add_m *new = (t_add_m *)malloc(sizeof(t_add_m) * 6);

    new->text = text;
    new->my = my;
    new->forw = forw;
    new->time_m = time_m;
    new->forw_from = NULL;
    new->reply_id = -1;
    return new;
}
