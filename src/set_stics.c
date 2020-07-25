#include "../inc/uchat.h"

void stic_click(GtkWidget *w, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next)
        i->check == true ? us = i : 0;
    add_file(us, create_struct((char *)gtk_widget_get_name(w),
         true, 0, NULL), 2, us->msg->next ? us->msg->next->id + 1 : 1);
}

static void init_signals_stics(t_main *m) {
    for (int i = 0; i < 37; i++)
        g_signal_connect(m->stic->but[i], "clicked", G_CALLBACK(stic_click), m); 
}

static void init_component(int i, t_main *m, int row, int col) {
    m->stic->way[i] = mx_backjoin("./source/resource/stic/", mx_itoa(i+1));
    if(i < 21)
        m->stic->way[i] = mx_delit_fre(m->stic->way[i], ".png");
    else
        m->stic->way[i] = mx_delit_fre(m->stic->way[i], ".gif");
    m->stic->img[i] = resize_proportion(m->stic->way[i], 50, 50);
    m->stic->but[i] = gtk_button_new ();
    gtk_widget_set_size_request(m->stic->but[i], 50, 50);
    gtk_widget_set_opacity (m->stic->but[i], 0.0);
    gtk_widget_set_name(m->stic->but[i], m->stic->way[i]);
    gtk_grid_attach(GTK_GRID(m->grid_stic), m->stic->img[i], col, row, 1, 1);
    gtk_grid_attach(GTK_GRID(m->grid_stic), m->stic->but[i], col, row, 1, 1);
}

void set_stics(t_main *m) {
    int row = 0;
    int col = 0;
    m->stic->img = (GtkWidget **)malloc(sizeof(GtkWidget *) * 37);
    m->stic->but = (GtkWidget **)malloc(sizeof(GtkWidget *) * 37);
    m->stic->way = (char **)malloc(sizeof(char *) * 37);
    m->grid_stic = gtk_grid_new();

    gtk_grid_insert_row(GTK_GRID(m->grid_stic), row);
    gtk_grid_insert_column(GTK_GRID(m->grid_stic), col);
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_stic), 8);
    gtk_grid_set_column_spacing(GTK_GRID(m->grid_stic), 8);
    for (int i = 0; i < 37; i++) {
        init_component(i, m, row, col);
        if ((i + 1)/3 > row)
            col = 0;
        else col++;
        row = (i + 1)/3; 
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_stic), m->grid_stic, 15, 50);
    init_signals_stics(m);
}
