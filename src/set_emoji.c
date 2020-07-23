#include "../inc/uchat.h"

void emo_click(GtkWidget *w, t_main *m) {
    char *cur;
    char *utf;
   //char tmp[4] = {0xE2, 0x98, 0xBA, '\0'};
    utf = m->emo->utf[mx_atoi((char *) gtk_widget_get_name(w))];
    cur = (char *)gtk_entry_get_text(GTK_ENTRY(m->edit_entry));
    cur = mx_strjoin(cur, utf);
    gtk_entry_set_text (m->sms, cur);
    //mx_printstr(emo);
}

static void init_signals_emo(t_main *m) {
    for (int i = 0; i < 21; i++)
        g_signal_connect(m->emo->but[i], "clicked", G_CALLBACK(emo_click), m); 
}
static void set_utf(t_main *m) {
    char tmp[4] ={0xE2, 0x98, 0xBA, '\0'};
    char tmp1[5] ={0xF0, 0x9F, 0x98, 0x84, '\0'};
    char tmp2[5] ={0xF0, 0x9F, 0x99, 0x83, '\0'};
    char tmp3[5] ={0xF0, 0x9F, 0x98, 0x86, '\0'};
    char tmp4[5] ={0xF0, 0x9F, 0x98, 0xB5, '\0'};

    char tmp5[5] ={0xF0, 0x9F, 0x98, 0x98, '\0'};
    char tmp6[5] ={0xF0, 0x9F, 0x98, 0xA2, '\0'};
    char tmp7[5] ={0xF0, 0x9F, 0xA4, 0xAF, '\0'};
    char tmp8[5] ={0xF0, 0x9F, 0x99, 0x84, '\0'};
    char tmp9[5] ={0xF0, 0x9F, 0x98, 0x8D, '\0'};

    char tmp10[5] ={0xF0, 0x9F, 0xA5, 0xB5, '\0'};
    char tmp11[5] ={0xF0, 0x9F, 0x98, 0xAD, '\0'};
    char tmp12[5] ={0xF0, 0x9F, 0xA4, 0x91, '\0'};
    char tmp13[5] ={0xF0, 0x9F, 0x98, 0x90, '\0'};
    char tmp14[5] ={0xF0, 0x9F, 0x98, 0xB1, '\0'};

    char tmp15[5] ={0xF0, 0x9F, 0xA4, 0xAC, '\0'};
    char tmp16[5] ={0xF0, 0x9F, 0x98, 0xB3, '\0'};
    char tmp17[5] ={0xF0, 0x9F, 0x98, 0x88, '\0'};
    char tmp18[5] ={0xF0, 0x9F, 0xA4, 0x94, '\0'};
    char tmp19[5] ={0xF0, 0x9F, 0x98, 0x8E, '\0'};

    char tmp20[5] ={0xF0, 0x9F, 0xA4, 0xAC, '\0'};
    char tmp21[5] ={0xF0, 0x9F, 0x98, 0xB3, '\0'};
    char tmp22[5] ={0xF0, 0x9F, 0x98, 0x88, '\0'};
    char tmp23[5] ={0xF0, 0x9F, 0xA4, 0x94, '\0'};
    char tmp24[5] ={0xF0, 0x9F, 0x98, 0x8E, '\0'};

    char tmp25[5] ={0xF0, 0x9F, 0xA4, 0xAC, '\0'};
    char tmp26[5] ={0xF0, 0x9F, 0x98, 0xB3, '\0'};
    char tmp27[5] ={0xF0, 0x9F, 0x98, 0x88, '\0'};

    // char tmp[4] ={ {0xE2, 0x98, 0xBA, '\0'};}
    // char tmp[4] ={ {0xE2, 0x98, 0xBA, '\0'};}
    m->emo->utf[0] = mx_strdup(tmp);
    m->emo->utf[1] = mx_strdup(tmp1);
    m->emo->utf[2] = mx_strdup(tmp2);
    m->emo->utf[3] = mx_strdup(tmp3);
    m->emo->utf[4] = mx_strdup(tmp4);

    m->emo->utf[5] = mx_strdup(tmp5);
    m->emo->utf[6] = mx_strdup(tmp6);
    m->emo->utf[7] = mx_strdup(tmp7);
    m->emo->utf[8] = mx_strdup(tmp8); 
    m->emo->utf[9] = mx_strdup(tmp9); 

    m->emo->utf[10] = mx_strdup(tmp10); 
    m->emo->utf[11] = mx_strdup(tmp11); 
    m->emo->utf[12] = mx_strdup(tmp12); 
    m->emo->utf[13] = mx_strdup(tmp13); 
    m->emo->utf[14] = mx_strdup(tmp14);

    m->emo->utf[15] = mx_strdup(tmp15); 
    m->emo->utf[16] = mx_strdup(tmp16); 
    m->emo->utf[17] = mx_strdup(tmp17); 
    m->emo->utf[18] = mx_strdup(tmp18); 
    m->emo->utf[19] = mx_strdup(tmp19); 

    // m->emo->utf[20] = "U+1F637"; 0xF0 0x9F 0x98 0xB7
    // m->emo->utf[21] = "U+1F929"; 0xF0 0x9F 0xA4 0xA9
    // m->emo->utf[22] = "U+1F92E"; 0xF0 0x9F 0xA4 0xAE
    // m->emo->utf[23] = "U+1F47B"; 	0xF0 0x9F 0x91 0xBB
    // m->emo->utf[24] = "U+1F4A9"; 	0xF0 0x9F 0x92 0xA9

    // m->emo->utf[25] = "U+1F47D"; 0xF0 0x9F 0x91 0xBD
    // m->emo->utf[26] = "U+1F64F"; 0xF0 0x9F 0x99 0x8F
    // m->emo->utf[27] = "U+1F44D"; 	0xF0 0x9F 0x91 0x8D
}

// static void set_utf(t_main *m) {
//     m->emo->utf[0] = "U+263A";
//     m->emo->utf[1] = "U+1F604";
//     m->emo->utf[2] = "U+1F643";
//     m->emo->utf[3] = "U+1F606";
//     m->emo->utf[4] = "U+1F635";
//     m->emo->utf[5] = "U+1F618";
//     m->emo->utf[6] = "U+1F622";
//     m->emo->utf[7] = "U+1F92F";
//     m->emo->utf[8] = "U+1F644";
//     m->emo->utf[9] = "U+1F60D";
//     m->emo->utf[10] = "U+1F975";
//     m->emo->utf[11] = "U+1F62D";
//     m->emo->utf[12] = "U+1F911";
//     m->emo->utf[13] = "U+1F610";
//     m->emo->utf[14] = "U+1F631";
//     m->emo->utf[15] = "U+1F92C";
//     m->emo->utf[16] = "U+1F633";
//     m->emo->utf[17] = "U+1F608";
//     m->emo->utf[18] = "U+1F914";
//     m->emo->utf[19] = "U+1F60E";
//     m->emo->utf[20] = "U+1F637";
//     m->emo->utf[21] = "U+1F929";
//     m->emo->utf[22] = "U+1F92E";
//     m->emo->utf[23] = "U+1F47B";
//     m->emo->utf[24] = "U+1F4A9";
//     m->emo->utf[25] = "U+1F47D";
//     m->emo->utf[26] = "U+1F64F";
//     m->emo->utf[27] = "U+1F44D";
// }

static void init_component(int i, t_main *m, int row, int col) {
    char *name = mx_itoa(i);
    char *tmp = mx_backjoin("./src/resource/emoji/", mx_itoa(i+1));

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
