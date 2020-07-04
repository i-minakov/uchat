#ifndef UCHAT_H

#include "../libmx/inc/libmx.h"
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INDENT_YOU(len) (len > 49 ?  250 : (250 + len*10)/2)

typedef struct s_size_alloc {
    int x;
    int y;
    int width;
    int height;
}              t_rect;

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
    struct s_data_users *head;
    struct s_data_users *next;
}              t_user;

typedef struct s_main {
    GtkWidget *window;
    GtkWidget *fix1;
    GtkWidget *sms;
    GtkWidget *but1;
    GtkWidget *grid_user;
    GtkWidget *fix_for_users;
    GtkWidget *fix_for_text;
    GtkWidget *lab_start;
    GtkWidget *fix_cap;
    GtkWidget *burger_but;
    GtkWidget *burger_but_img;
    GtkWidget *my_photo;
    GtkWidget *frame_for_my_photo;
    GtkWidget *friend_name;
    GtkBuilder *builder;
    char *text;
    struct s_data_users *users;
}              t_main;

t_user *mx_create_user();
void free_users(t_user **list);
void set_users(t_main *m);
void reset_users(t_main *m);
void send_but(GtkWidget *wid, t_main *m);
void user_click(GtkWidget *wid, t_user *users);
GtkWidget *resize_image(const char *path_to_image, uint width, uint heigh);

char *mx_strpart(char *str, int index);

#endif 
