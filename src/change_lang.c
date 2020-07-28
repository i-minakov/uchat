#include "../inc/uchat.h"

static void set_and_stic(t_main *m) {
    gtk_button_set_label(GTK_BUTTON(m->set->my_name), 
    MX_NAME(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->set->my_pas), 
    MX_PAS(m->style->lang));
    gtk_label_set_text(GTK_LABEL(m->set->color_text), 
    MX_COLOR(m->style->lang));
    gtk_label_set_text(GTK_LABEL(m->set->lang_text), 
    MX_LANG(m->style->lang));
    gtk_label_set_text(GTK_LABEL(m->set->notif_text), 
    MX_NOT(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->stic_smile), 
    MX_EMOJI(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->stic_stic),  
    MX_STICS(m->style->lang));
}

static void ch_lang(t_main *m) {
    gtk_label_set_text(GTK_LABEL(m->lab_start), MX_START(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->menu->exit), 
        MX_MENU_EX(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->menu->settings), 
        MX_MENU_SET(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->menu->contacts), 
    MX_MENU_CONT(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->menu->search), 
    MX_MENU_SEA(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->menu->black_list),  
    MX_MENU_BLL(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->dots->clear_msg_but), 
    MX_DOT_DEL(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->dots->block_but), 
    MX_DOT_BL(m->style->lang));
    gtk_button_set_label(GTK_BUTTON(m->dots->search_msg_but), 
    MX_DOT_FI(m->style->lang));
    set_and_stic(m);
}

void change_lang(GtkToggleButton *togglebutton, t_main *m) {
    char *str = NULL;

    (void)togglebutton;
    if (m->style->start_c == 0) {
        if (m->style->lang == 1) 
            m->style->lang = 2;
        else 
            m->style->lang = 1;
    }
    ch_lang(m);
    if (m->style->start_c == 0) {
        str = mx_itoa(m->style->color - 1);
        m->command = mx_arrjoin(m->command, "mx_set_type");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, str);
        m->command = mx_arrjoin(m->command, "0");
        free(str);
    }
    else {
        m->style->start_c = 0;
        if (m->style->lang == 2) {
            g_signal_handlers_block_by_func(m->set->lang1, (gpointer) change_lang, m);
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(m->set->lang2), TRUE);
            g_signal_handlers_unblock_by_func(m->set->lang1, (gpointer) change_lang, m);
        }
    }
}

