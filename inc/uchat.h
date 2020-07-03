#ifndef UCHAT_H

#include "../libmx/inc/libmx.h"
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INDENT_YOU(len) (len > 50 ? 174 : 574 - len*10)

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
