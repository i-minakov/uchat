#ifndef UCHAT_H

#include "../libmx/inc/libmx.h"
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MX_BOX_END(wid, label) gtk_box_pack_end(GTK_BOX(wid), label, FALSE, FALSE, 10)
#define MX_BOX_START(wid, label) gtk_box_pack_start(GTK_BOX(wid), label, FALSE, FALSE, 10)
#define MX_MSG_PACK(flag, label, box) (flag == true ? MX_BOX_END(box, label) : MX_BOX_START(box, label))

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
    bool check;
    int row;
    int count;
    int y_chat;
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
    struct s_main *m;
}              t_cap;

typedef struct s_menu {
    GtkWidget *menu_box;
    GtkWidget *menu_img;
    GtkWidget *color_text;
    GtkWidget *lang_text;
    GtkWidget *lang1;
    GtkWidget *lang2;
    GtkWidget *color1;
    GtkWidget *color2;
    GtkWidget *user_search;
    int flag;
    
}              t_menu;

typedef struct s_main {
    GtkWidget *window;
    GtkWidget *fix1;
    GtkWidget *sms;
    GtkWidget *but1;
    GtkWidget *grid_user;
    GtkWidget *fix_for_users;
    GtkWidget *fix_for_text;
    GtkWidget *lab_start;
    GtkWidget *scrol_bar;
    GtkWidget *edit_entry;
    GtkWidget *file_ch;
    GtkAdjustment *adj; 
    GtkBuilder *builder;
    char *text;
    struct s_cap *cap;
    struct s_data_users *users;
    struct s_menu *menu;
    struct s_style *style;
}              t_main;

int start(void);

t_user *mx_create_user();
void free_users(t_user **list);
void set_users(t_main *m);
void reset_users(t_main *m);
void send_but(GtkWidget *wid, t_main *m);
void user_click(GtkWidget *wid, t_user *users);
GtkWidget *resize_image(const char *path_to_image, uint width, uint heigh);
void msg_pushfront(t_msg **head, char *text);
void reset_l_mess(t_user *i);
char *mx_strpart(char *str, int index);
void free_msg(t_msg **list);
t_msg *create_msg(char *text, char *filename);
void delete_msg(GtkMenuItem *item, t_msg *msg);
void forward_msg(GtkMenuItem *item, t_msg *msg);
void add_file(t_main *m, gchar *tmp);
void init_signals(t_main *m);
void save_file(GtkMenuItem *item, t_msg *msg);

void burger_notify(GtkWidget *widget, GdkEvent *event, t_main *m);
void burger_leave(GtkWidget *widget, GdkEvent *event, t_main *m);
GtkWidget *resize_proportion(const char *path_to_image, int xs, int ys);

void switch_menu(GtkWidget *wid, t_main *m);

#endif 
