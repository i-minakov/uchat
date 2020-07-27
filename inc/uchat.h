#ifndef UCHAT_H
#define UCHAT_H

#include "../libmx/inc/libmx.h"
#include "ssl.h"
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MX_DEF_PHOTO "source/resource/default.jpg"
#define MX_SCROL_END(m) g_idle_add((GSourceFunc)move_scrol, m)
#define MX_SET_NAME_MSG(flag, label) flag == true ? gtk_widget_set_name(label, "lm") : gtk_widget_set_name(label, "lm2")
#define MX_SHOW_HIDE(flag, widget) flag == 1 ? gtk_widget_show(widget) : gtk_widget_hide(widget) 
#define MX_BOX_END(wid, label) gtk_box_pack_end(GTK_BOX(wid), label, FALSE, FALSE, 0)
#define MX_BOX_START(wid, label) gtk_box_pack_start(GTK_BOX(wid), label, FALSE, FALSE, 10)
#define MX_MSG_PACK(flag, label, box) (flag == true ? MX_BOX_END(box, label) : MX_BOX_START(box, label))

#define MX_MY_PHOTO(flag) flag == 1 ? "./source/resource/my photo.png" : "./source/resource/activated photo2.png"
#define MX_NAME_COLOR(flag) flag == 1 ? "<span color=\"white\" font=\"14\">%s</span>" : "<span color=\"black\" font=\"14\">%s</span>"
#define MX_CSS(flag) flag == 1 ? "./src/black.css" : "./src/light.css"
#define MX_BOTTOM(flag) flag == 1 ? "./source/resource/bottom.png" : "./source/resource/bottom1.png"
#define MX_TOP(flag) flag == 1 ? "./source/resource/top.png" : "./source/resource/top1.png"
#define MX_ACTIVE(flag) flag == 1 ? "./source/resource/activated.png" : "./source/resource/activated2.png"
#define MX_SLEPT(flag) flag == 1 ? "./source/resource/slept.png" : "./source/resource/slept22.png"
#define MX_ACT_PH(flag) flag == 1 ? "./source/resource/activated photo.png" : "./source/resource/activated photo2.png"
#define MX_SL_PH(flag) flag == 1 ? "./source/resource/slept photo.png" : "./source/resource/slept photo2.png"
#define MX_ICON_ENTRY_PR(flag) flag == 1 ? "./source/resource/attach.png" : "./source/resource/attach1.png"
#define MX_ICON_ENTRY_SEC(flag) flag == 1 ? "./source/resource/smile.png" : "./source/resource/smile1.png"
 
#define MX_START(flag) flag == 2 ? "Выберите чат, чтобы начать переписку" : "Please select a chat to start messaging"
#define MX_MENU_EX(flag) flag == 2 ? "Выход" : "Exit"
#define MX_MENU_SET(flag) flag == 2 ? "Настройки" : "Settings"
#define MX_MENU_CONT(flag) flag == 2 ? "Контакты" : "Contacts"
#define MX_MENU_BLL(flag) flag == 2 ? "Чёрный список" : "Black list"
#define MX_MENU_SEA(flag) flag == 2 ? "Поиск" : "Search"

#define MX_DOT_DEL(flag) flag == 2 ? "Удалить чат" : "Delete chat"
#define MX_DOT_BL(flag) flag == 2 ? "Заблокировать" : "Block user"
#define MX_DOT_FI(flag) flag == 2 ? "Поиск по сообщениям" : "Find massage"

#define MX_NOT(flag) flag == 2 ? "Уведомления" : "Notifications"
#define MX_NAME(flag) flag == 2 ? "Имя" : "Name"
#define MX_PAS(flag) flag == 2 ? "Пароль" : "Password"
#define MX_COLOR(flag) flag == 2 ? "Тема" : "Theme"
#define MX_LANG(flag) flag == 2 ? "Язык" : "language"

#define MX_EMOJI(flag) flag == 2 ? "Емоджи" : "Emoji"
#define MX_STICS(flag) flag == 2 ? "Стикеры" : "Stickers"

enum e_cmd {
    SRCH_MSG, 
    SRCH_US,
    BLCK,
    DEF,
    SIG_UP,
    SIG_IN,
    USERS,
    THEME,
    LANG,
    CHECK_PASS,
    CHECK_US,
    UPDATE_SIZE,
    LOG_OUT,
    BLACK_LIST
};

typedef struct s_add_msg {
    char *text;
    bool my; 
    int forw;
    char *time_m;
    char *forw_from;
    int reply_id;
    int id;
}              t_add_m;

typedef struct s_msg_forward {
    char *text; 
    char *filename;
    char *autor;
    bool my;
    int was_forw;
    int stic;
    struct s_forward *f;
}              t_msg_forw;

typedef struct s_size {
    int x;
    int y;
    float w;
    float h;
    float xs;
    float ys;
} 				t_size;

typedef struct s_style {
    int lang;
    int color;
}              t_style;

typedef struct s_message {
    int id;
    int count;
    char *text;
    char *filename;
    char *time; 
    gdouble adj_value;
    GtkWidget *menu;
    GtkWidget *file;
    GtkWidget *label;
    bool my;
    int stic;
    int forward;
    struct s_data_users *user;
    struct s_message *prev;
    struct s_message *next;
}              t_msg;

typedef struct s_sticker {
    GtkWidget **img;
    GtkWidget **but;
    char **way;
}              t_sticker;

typedef struct s_emoji {
    GtkWidget **img;
    GtkWidget **but;
    char **utf;
}              t_emoji;

typedef struct s_data_users {
    int row;
    int count;
    bool check;
    char *name;
    GtkWidget *but;
    GtkWidget *fix;
    GtkWidget *img;
    int size_request;
    char *photo_name;
    GtkWidget *newmsg;
    GtkWidget *l_name;
    GtkWidget *l_mess;
    GtkWidget *l_time;
    GtkWidget *text_grid;
    GtkWidget *backg_us_slept;
    GtkWidget *backg_us_activ;
    GtkWidget *frame_photo_act;
    GtkWidget *frame_photo_slept;
    struct s_main *m;
    struct s_message *msg;
    struct s_data_users *head;
    struct s_data_users *next;
}              t_user;

typedef struct s_cap {
    GtkWidget *fix_cap;
    GtkWidget *top_b;
    GtkWidget *burger_but;
    GtkWidget *burger_but_img;
    GtkWidget *my_photo;
    GtkWidget *frame_for_my_photo;
    GtkWidget *friend_name;
    GtkWidget *dot_menu;
    GtkWidget *dot_menu_but;
    GtkWidget *my_name;
    struct s_main *m;
}              t_cap;

typedef struct s_setting {
    GtkWidget *sett_box;
    GtkWidget *sett_fix;
    GtkWidget *color_text;
    GtkWidget *lang_text;
    GtkWidget *notif_text;
    GtkWidget *notif1;
    GtkWidget *lang1;
    GtkWidget *lang2;
    GtkWidget *color1;
    GtkWidget *color2;
    GtkWidget *my_name;
    GtkWidget *my_pas;
    GtkWidget *my_frame;
    GtkWidget *my_frame2;
    GtkWidget *my_photo;
    GtkWidget *set_but;
    GtkWidget *chan_ph;
    GtkWidget *chan_name;
    GtkWidget *chan_pas;
    int flag; 
}              t_setting;

typedef struct s_menu {
    GtkWidget *menu_box;
    GtkWidget *menu_fix;
    GtkWidget *search;
    GtkWidget *settings;
    GtkWidget *contacts;
    GtkWidget *exit;
    GtkWidget *black_list;

    GtkWidget *setic;
    GtkWidget *setic2;
    GtkWidget *searchic;
    GtkWidget *searchic2;
    GtkWidget *exic;
    GtkWidget *exic2;
    GtkWidget *contic;
    GtkWidget *contic2;
    GtkWidget *blackic;
    GtkWidget *blackic2;
    int flag;
    
}              t_menu;

typedef struct s_dot_menu {
    int visible;
    GtkWidget *dot_img;
    GtkWidget *dot_but;
    GtkWidget *fix_dot_menu;
    GtkWidget *search_msg_but;
    GtkWidget *clear_msg_but;
    GtkWidget *block_but;
    struct s_main *m;
}              t_dots;

typedef struct s_forward {
    GtkWidget *forw_img;
    GtkWidget *fix_forw;
    GtkWidget *search_forw;
    GtkWidget *fox_for_forw;
    GtkWidget *grid_forw;
    GtkWidget *but_cancel;
    struct s_msg_forward *fm;
    struct s_main *m;
}              t_forw;

typedef struct s_search
{
    char *name;
    char *path;
    GtkWidget* but;
    struct s_main *m;
    struct s_search *next;
}              t_search;


typedef struct s_main {
    GtkCssProvider *css;
    GtkCssProvider *css2;
    GtkWidget *search;
    GtkWidget *window;
    GtkWidget *fix1;
    GtkWidget *sms;
    GtkWidget *but1;
    GtkWidget *grid_user;
    GtkWidget *grid_search;

    GtkWidget *stic_fix_img;
    GtkWidget *grid_stic;
    GtkWidget *grid_emo;
    GtkWidget *fix_for_stic;
    GtkWidget *stic_scrol;
    GtkWidget *stic_smile;
    GtkWidget *stic_stic;
    GtkWidget *stic_line;

    GtkWidget *micro_on;
    GtkWidget *micro_of;
    GtkWidget *micro_on_but;
    GtkWidget *micro_of_but;
    int micro_flag;

    GtkWidget *fix_for_users;
    GtkWidget *fix_for_text;
    GtkWidget *lab_start;
    GtkWidget *scrol_bar;
    GtkWidget *edit_entry;
    GtkWidget *bottom_b;
    GtkAdjustment *adj; 
    GtkBuilder *builder;
    char **command;
    int exit;
    int order;
    int cmd;
    int flag_search; // 1 - msg, 2 - users, 3 - contacts
    char *text;
    char *my_name;
    char *search_str;
    int count_reqw;
    int count_reqw_edit;
    int bl;
    struct s_forward *forw;
    struct s_dot_menu *dots;
    struct s_cap *cap;
    struct s_data_users *users;
    struct s_sticker *stic;
    struct s_emoji *emo;
    struct s_menu *menu;
    struct s_style *style;
    struct s_setting *set;
    struct s_search *srch;
    struct s_wid *log_in;
}              t_main;

int chat_screen(t_main **gtk);
int log_screen(t_main *m);
int interface();

void mx_hide(GtkWidget *w);
void mx_show(GtkWidget *wid);
t_main *malloc_main();
t_user *mx_create_user(char *name, char *path);
void user_pushback(t_user **head, char *name);
void free_users(t_user **list);
void set_users(t_main *m);
void reset_users(t_main *m);
void send_but(GtkWidget *wid, t_main *m);
void user_click(GtkWidget *wid, t_user *users);
GtkWidget *resize_image(const char *path_to_image, guint width, guint heigh);
void msg_pushfront(t_msg **head, char *text, bool my, int forw);
void reset_l_mess(t_user *i);
char *mx_strpart(char *str, int index);
void free_msg(t_msg **list);
t_msg *create_msg(char *text, char *filename);
void delete_msg(GtkMenuItem *item, t_msg *msg);
void forward_msg(GtkMenuItem *item, t_msg *msg);
void add_file(t_user *us, t_add_m *s, int stic, int id);
void init_signals(t_main *m);
void save_file(GtkMenuItem *item, t_msg *msg);
void add_message(t_user *i, t_add_m *s, int id);
void forward_msg(GtkMenuItem *item, t_msg *msg);
void edit_msg(GtkMenuItem *item, t_msg *msg);
void search_activ(GtkEntry *e, t_main *m);
void show_hide_back_us(t_user *users);
void reply_msg(GtkMenuItem *item, t_msg *msg);
t_add_m *create_struct(char *text, bool my, int forw, char *time_m);
void move_scrol(t_main *m);
void add_message_back(t_user *i, t_add_m *s, int count, int id);
void popup_menu(GtkButton *widget, GdkEventButton  *event, t_msg *msg);
void command_msg(t_user *us, t_add_m *s, int flag);
t_user *mx_user_by_name(char *name, char *path, t_main *m);
void set_chat_grid(t_main *m, int flag);
t_search *mx_create_node_search(char *name, char *path);
void pushfront_search_contact(t_search **head, t_main *m, char *name, char *path);
void user_pushfront(t_user **head, char *name, char *path);
void show_result_of_search(t_list *list, t_main *m);
void clear_history(GtkWidget *wid, t_main *m);
int mx_msg_size(t_msg *list);
void mx_new_msg_back(t_user *us, t_list *new);
void file_check(gchar *tmp, t_msg **msg, char *name, bool my);
void add_file_back(t_user *us, t_add_m *s, int stic, int count);
void add_time(t_user *i, t_add_m *s);
t_user *mx_activ_us(t_main *m);
void free_all(t_main *m);
void mx_idle_show(bool flag, GtkWidget *wid);
void mx_idle_hide(bool flag, GtkWidget *wid);
t_msg *mx_msg_by_id(t_user *us, int id);
void mx_blacklist(t_main *m, t_list *list);
void mx_destroy(GtkWidget *wid);
void mx_idle_destroy(bool flag, GtkWidget *wid);
void mx_remove_user_by_name(t_user **users, char *name);
void mx_msg_or_file(char **arr, char *id, t_user *us);
void result_msg(t_list *list, t_main *m);

void init_main_stuff(t_main *m);
void init_menu(t_main *m);
void init_set(t_main *m);
void init_dot_forv(t_main *m);

void burger_notify(GtkWidget *widget, GdkEvent *event, t_main *m);
void burger_leave(GtkWidget *widget, GdkEvent *event, t_main *m);
GtkWidget *resize_proportion(const char *path_to_image, int xs, int ys);

void switch_menu(GtkWidget *wid, t_main *m);
void show_menu(t_main *m);
void hide_menu(t_main *m);
void hide_set(t_main *m);
void show_set(t_main *m);

void connect_css(t_main *m, int flag);
void change_color(GtkToggleButton *togglebutton, t_main *m);
void change_lang(GtkToggleButton *togglebutton, t_main *m);
void change_notif(GtkToggleButton *togglebutton, t_main *m);
void change_name(GtkEntry *e, t_main *m);
void backto_name(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m);
void enter_name(GtkWidget *widget, t_main *m);
void change_pas(GtkEntry *e, t_main *m);
void backto_pas(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m);
void enter_pas(GtkWidget *widget, t_main *m);

void micro_start(GtkWidget *w, t_main *m);
void micro_end(GtkWidget *w, t_main *m);
void icon_entr_set(t_main *m);
void first_emo_set(t_main *m);
void set_emo_tab(t_main *m);
void set_stics(t_main *m);
void set_emoji(t_main *m);
void stic_on(GtkWidget *w, t_main *m);
void emo_on(GtkWidget *w, t_main *m);
void stic_click(GtkWidget *w, t_main *m);
void stic_free(t_main *m);
void the_ic(int flag, t_main *m);

void attach_file(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m);
void mx_exit(GtkWidget *object, t_main *m);
<<<<<<< HEAD

=======
void mx_voice(t_main *m);
>>>>>>> e409225ed72415ebbb9af41349e3cd1adfb97638

/////////////////////////////////////////////////////////////////////////////
// Olya login screen
/////////////////////////////////////////////////////////////////////////////

typedef struct s_login {
	GtkWidget *log_hower;
	GtkWidget *log_hower2;
	GtkWidget *log_gif;
	GtkWidget *log_text;
	GtkWidget *log_name;
	GtkWidget *log_pas;
	GtkWidget *log_but;
	GtkWidget *no_fil_log;
	char *logname;
	char *logpas;
} 			t_login;

typedef struct s_sign {
	GtkWidget *sig_hower;
	GtkWidget *sig_hower2;
	GtkWidget *sig_gif;
	GtkWidget *sig_text;
	GtkWidget *sig_name;
	GtkWidget *sig_pas;
	GtkWidget *sig_pas2;
	GtkWidget *sig_photo;
    GtkWidget *sig_add_img;
	GtkWidget *sig_display;
	int flagimg;
	GtkWidget *sig_but;
	GtkWidget *no_fil_sig;
	char *signame;
	char *sigpas;
	char *sigpas2;
	char *sigfile;
} 			t_sign;

typedef struct s_wid {
	GtkBuilder *builder; 
    GtkWidget *window;
	GtkWidget *fixed;
    GtkWidget *start_gif;
    GtkWidget *wait_gif;
	GtkWidget *badact;
	GtkWidget *badact_but;
	GtkWidget *badact_lab;
	GtkWidget *black_back;
    struct s_sign *sig;
    struct s_login *log;
    struct s_main *m;
} 			t_wid;

typedef struct s_eye {
	bool log;
	bool sig;
	bool sig2;
    struct s_wid *wid;

} 				t_eye;

typedef struct s_sizefoto {
		int x;
    	int y;
		int w;
    	int h;
} 				t_sizefoto;


void init_widgets_start(t_wid *wid, t_eye *eye);
void init_signals_start(t_wid *wid, t_eye *eye);

void log_click(GtkWidget *widget, t_wid *wid);
void sign_click(GtkWidget *widget, t_wid *wid);
void show_fields(t_wid *wid);
void hide_start(t_wid *wid);

void log_hover(GtkWidget *widget, GdkEventButton *event, t_wid *wid);
void sig_hover(GtkWidget *widget, GdkEventButton *event, t_wid *wid);

void sig_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid);
void log_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid);

void log_ok(GtkWidget *widget, t_wid *wid);
void sig_ok(GtkWidget *widget, t_wid *wid);

void add_sig_photo(GtkWidget *widget, t_wid *wid);
GtkWidget *resize_image_correct(const char *path_to_image);

 void make_vis(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye);
void make_vis1(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye);
void make_vis2(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye);

void bad_act(t_wid *wid, int flag, int thred);
void hide_bad(GtkWidget *widget, t_wid *wid);

#endif
