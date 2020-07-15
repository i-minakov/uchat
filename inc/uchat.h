#ifndef UCHAT_H

#include "../libmx/inc/libmx.h"
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MX_SHOW_HIDE(flag, widget) flag == 1 ? gtk_widget_show(widget) : gtk_widget_hide(widget) 
#define MX_BOX_END(wid, label) gtk_box_pack_end(GTK_BOX(wid), label, FALSE, FALSE, 10)
#define MX_BOX_START(wid, label) gtk_box_pack_start(GTK_BOX(wid), label, FALSE, FALSE, 10)
#define MX_MSG_PACK(flag, label, box) (flag == true ? MX_BOX_END(box, label) : MX_BOX_START(box, label))

#define MX_MY_PHOTO(flag) flag == 1 ? "./src/resource/my photo.png" : "./src/resource/activated photo2.png"
#define MX_NAME_COLOR(flag) flag == 1 ? "<span color=\"white\" font=\"14\">\%s</span>" : "<span color=\"black\" font=\"14\">\%s</span>"
#define MX_CSS(flag) flag == 1 ? "./src/black.css" : "./src/light.css"
#define MX_BOTTOM(flag) flag == 1 ? "./src/resource/bottom.png" : "./src/resource/bottom1.png"
#define MX_TOP(flag) flag == 1 ? "./src/resource/top.png" : "./src/resource/top1.png"
#define MX_ACTIVE(flag) flag == 1 ? "./src/resource/activated.png" : "./src/resource/activated2.png"
#define MX_SLEPT(flag) flag == 1 ? "./src/resource/slept.png" : "./src/resource/slept2 1.png"
#define MX_ACT_PH(flag) flag == 1 ? "./src/resource/activated photo.png" : "./src/resource/activated photo2.png"
#define MX_SL_PH(flag) flag == 1 ? "./src/resource/slept photo.png" : "./src/resource/slept photo2.png"

#define MX_START(flag) flag == 2 ? "Выберите чат, чтобы начать переписку" : "Please select a chat to start messaging"
#define MX_MENU_EX(flag) flag == 2 ? "Выход" : "Exit"
#define MX_MENU_SET(flag) flag == 2 ? "Настройки" : "Settings"
#define MX_MENU_CONT(flag) flag == 2 ? "Контакты" : "Contacts"
#define MX_MENU_SEA(flag) flag == 2 ? "Поиск" : "Search"

#define MX_DOT_DEL(flag) flag == 2 ? "Удалить чат" : "Delete chat"
#define MX_DOT_BL(flag) flag == 2 ? "Заблокировать" : "Block user"
#define MX_DOT_FI(flag) flag == 2 ? "Поиск по сообщениям" : "Find massage"

#define MX_COLOR(flag) flag == 2 ? "Тема" : "Theme"
#define MX_LANG(flag) flag == 2 ? "Язык" : "language"

typedef struct s_msg_forward {
    char *text; 
    char *filename;
    char *autor;
    bool my;
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
    int count;
    char *text;
    char *filename;
    gdouble adj_value;
    GtkWidget *menu;
    GtkWidget *file;
    GtkWidget *label;
    bool my;
    struct s_data_users *user;
    struct s_message *prev;
    struct s_message *next;
}              t_msg;

typedef struct s_data_users {
    GtkWidget *but;
    GtkWidget *fix;
    GtkWidget *l_name;
    GtkWidget *l_mess;
    GtkWidget *img;
    GtkWidget *l_time;
    GtkWidget *text_grid;
    GtkWidget *backg_us_slept;
    GtkWidget *backg_us_activ;
    GtkWidget *frame_photo_act;
    GtkWidget *frame_photo_slept;
    char *name;
    bool check;
    int row;
    int count;
    int y_chat;
    char *photo_name;
    struct s_main *m;
    struct s_message *msg;
    struct s_data_users *head;
    struct s_data_users *next;
}              t_user;

typedef struct s_cap {
    GtkWidget *fix_cap;
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
    GtkWidget *lang1;
    GtkWidget *lang2;
    GtkWidget *color1;
    GtkWidget *color2;
    GtkWidget *my_name;
    GtkWidget *my_frame;
    GtkWidget *my_frame2;
    GtkWidget *my_photo;
    GtkWidget *set_but;
    int flag; 
}              t_setting;

typedef struct s_menu {
    GtkWidget *menu_box;
    GtkWidget *menu_fix;
    GtkWidget *search;
    GtkWidget *settings;
    GtkWidget *contacts;
    GtkWidget *exit;
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
    GtkWidget *fix_for_users;
    GtkWidget *fix_for_text;
    GtkWidget *lab_start;
    GtkWidget *scrol_bar;
    GtkWidget *edit_entry;
    GtkWidget *bottom_b;
    GtkWidget *top_b;
    GtkAdjustment *adj; 
    GtkBuilder *builder;
    int exit;
    int flag_search; // 1 - msg, 2 - users, 3 - contacts
    char *text;
    struct s_forward *forw;
    struct s_dot_menu *dots;
    struct s_cap *cap;
    struct s_data_users *users;
    struct s_menu *menu;
    struct s_style *style;
    struct s_setting *set;
}              t_main;

int log_screen(void);
t_user *mx_create_user();
void free_users(t_user **list);
void set_users(t_main *m);
void reset_users(t_main *m);
void send_but(GtkWidget *wid, t_main *m);
void user_click(GtkWidget *wid, t_user *users);
GtkWidget *resize_image(const char *path_to_image, uint width, uint heigh);
void msg_pushfront(t_msg **head, char *text, bool my);
void reset_l_mess(t_user *i);
char *mx_strpart(char *str, int index);
void free_msg(t_msg **list);
t_msg *create_msg(char *text, char *filename);
void delete_msg(GtkMenuItem *item, t_msg *msg);
void forward_msg(GtkMenuItem *item, t_msg *msg);
void add_file(t_main *m, gchar *tmp);
void init_signals(t_main *m);
void save_file(GtkMenuItem *item, t_msg *msg);
void add_message(t_main *m, t_user *i, bool my);
void forward_msg(GtkMenuItem *item, t_msg *msg);
void edit_msg(GtkMenuItem *item, t_msg *msg);
void search_activ(GtkEntry *e, t_main *m);
void show_hide_back_us(t_user *users);
void login();

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

/////////////////////////////////////////////////////////////////////////////
// Olya login screen
/////////////////////////////////////////////////////////////////////////////

typedef struct s_wid {
	GtkBuilder *builder; 
    GtkWidget *window;
	GtkWidget *fixed;

	GtkWidget *log_hower;
	GtkWidget *sig_hower;
	GtkWidget *log_hower2;
	GtkWidget *sig_hower2;

	GtkWidget *log_gif;
	GtkWidget *sig_gif;

	GtkWidget *log_text;
	GtkWidget *log_name;
	GtkWidget *log_pas;
	GtkWidget *log_but;

	GtkWidget *sig_text;
	GtkWidget *sig_name;
	GtkWidget *sig_pas;
	GtkWidget *sig_pas2;
	GtkWidget *sig_photo;
	GtkWidget *sig_display;
	int flagimg;
	GtkWidget *sig_but;

	GtkWidget *no_fil_log;
	GtkWidget *no_fil_sig;
	GtkWidget *the_end;

	GtkWidget *badact;
	GtkWidget *badact_but;
	GtkWidget *badact_lab;
	GtkWidget *black_back;

	char *logname;
	char *logpas;
	char *signame;
	char *sigpas;
	char *sigpas2;
	char *sigfile;
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

void bad_act(t_wid *wid, int flag);
void hide_bad(GtkWidget *widget, t_wid *wid);
int log_screen(void);

#endif
