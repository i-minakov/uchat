#include "../inc/uchat.h"

static void first_choise(t_wid *wid) {
    //изначальный выбор нажатием + анимация
	g_signal_connect(wid->log->log_hower, "enter_notify_event", G_CALLBACK(log_hover), wid);
	g_signal_connect(wid->sig->sig_hower2, "enter_notify_event", G_CALLBACK(sig_hover), wid);
	g_signal_connect(wid->log->log_hower2, "clicked", G_CALLBACK(log_click), wid);
	g_signal_connect(wid->sig->sig_hower, "clicked", G_CALLBACK(sign_click), wid);

    //выбор ховером
	g_signal_connect(wid->sig->sig_gif, "enter_notify_event", G_CALLBACK(log_enter_notify_event), wid);
	g_signal_connect(wid->log->log_gif, "enter_notify_event", G_CALLBACK(sig_enter_notify_event), wid);

}

static void result(t_wid *wid) {
    //результирующие действия
	g_signal_connect(wid->log->log_but, "clicked", G_CALLBACK(log_ok), wid);
	g_signal_connect(wid->sig->sig_but, "clicked", G_CALLBACK(sig_ok), wid);
	g_signal_connect(wid->sig->sig_photo, "file-set", G_CALLBACK(add_sig_photo), wid);
}

void init_signals_start(t_wid *wid, t_eye *eye) {
	gtk_builder_connect_signals(wid->builder, wid->builder);
    first_choise(wid);
    result(wid);
    g_signal_connect(wid->log->log_pas, "icon_press", G_CALLBACK(make_vis), eye);
	g_signal_connect(wid->sig->sig_pas, "icon_press", G_CALLBACK(make_vis1), eye);
	g_signal_connect(wid->sig->sig_pas2, "icon_press", G_CALLBACK(make_vis2), eye);
	g_signal_connect(wid->badact_but, "clicked", G_CALLBACK(hide_bad), wid);
}
