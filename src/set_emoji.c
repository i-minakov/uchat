#include "../inc/uchat.h"

void emo_click(GtkWidget *w, t_main *m) {
    char *cur;
    char *utf;
    utf = m->emo->utf[mx_atoi((char *) gtk_widget_get_name(w))];
    cur = (char *)gtk_entry_get_text(GTK_ENTRY(m->sms));
    cur = mx_strjoin(cur, utf);
    gtk_entry_set_text (GTK_ENTRY(m->sms), cur);
    free(cur);
}

static void init_signals_emo(t_main *m) {
    for (int i = 0; i < 21; i++)
        g_signal_connect(m->emo->but[i], "clicked", G_CALLBACK(emo_click), m); 
}

static void set_utf(t_main *m) {
    char tmp25[5] ={0xF0, 0x9F, 0x91, 0xBD, '\0'};
    char tmp26[5] ={0xF0, 0x9F, 0x99, 0x8F, '\0'};
    char tmp27[5] ={0xF0, 0x9F, 0x91, 0x8D, '\0'};
    first_emo_set(m);

    m->emo->utf[25] = mx_strdup(tmp25);
    m->emo->utf[26] = mx_strdup(tmp26);
    m->emo->utf[27] = mx_strdup(tmp27);
}

static void init_component(int i, t_main *m, int row, int col) {
    char *name = mx_itoa(i);
    char *tmp = mx_backjoin("./source/resource/emoji/", mx_itoa(i+1));

    tmp = mx_delit_fre(tmp, ".png");
    m->emo->img[i] = resize_proportion(tmp, 35, 35);
    m->emo->but[i] = gtk_button_new ();
    gtk_widget_set_size_request(m->emo->but[i], 35, 35);
    gtk_widget_set_opacity (m->emo->but[i], 0.0);
    gtk_widget_set_name(m->emo->but[i], name);
    gtk_grid_attach(GTK_GRID(m->grid_emo), m->emo->img[i], col, row, 1, 1);
    gtk_grid_attach(GTK_GRID(m->grid_emo), m->emo->but[i], col, row, 1, 1);
    free(name);
    free(tmp);
}

void set_emoji(t_main *m) {
    int row = 0;
    int col = 0;
    m->emo->img = (GtkWidget **)malloc(sizeof(GtkWidget *) * 28);
    m->emo->but = (GtkWidget **)malloc(sizeof(GtkWidget *) * 28);
    m->emo->utf = (char **)malloc(sizeof(char *) * 28);
    m->grid_emo = gtk_grid_new();

    gtk_grid_insert_row(GTK_GRID(m->grid_emo), row);
    gtk_grid_insert_column(GTK_GRID(m->grid_emo), col);
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_emo), 8);
    gtk_grid_set_column_spacing(GTK_GRID(m->grid_emo), 8);
    for (int i = 0; i < 28; i++) {
        init_component(i, m, row, col);
        if ((i + 1)/4 > row)
            col = 0;
        else col++;
        row = (i + 1)/4; 
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_stic), m->grid_emo, 19, 50);
    init_signals_emo(m);
    set_utf(m);
}
