#ifndef DB_H
#define DB_H

#include <sqlite3.h>

typedef struct s_db {
    sqlite3 *db;
    sqlite3_stmt *res;
    int flag;
    char *command;
    char *err_msg;
}              t_db;

typedef struct s_table_list {
    int flag;
    char *name;
    char *path_img;
    char *last_mssg;
    char *last_mssg_time;
}              t_table_list;

typedef struct s_history {
    int id;
    char *message;
    char *time;
    char *name;
    char *mssg_id;
    char *forward;
    char *file_name;
    char *flag;
    char *r_f_mssg;
    char *r_f_time;
}              t_history;

typedef struct s_input {
    char *name_from;
    char *file_name;
    char *forward;
    char *name_to;
    char *message;
    char *reply;
    int flag;
}              t_input;

t_list *mx_get_tables_list(void);
t_list *mx_send_list_back(char *name, int flag);
t_list *mx_user_search(char *part_name, char *size);
t_list *mx_history_back(char *name_from, char *name_to, char *size);
t_list *mx_mssg_search(char *name, char *another_name, char *part_mssg, char *size);
bool mx_part_cmp(char *data, char *part_name);
bool mx_check_user_pass(char *name, char *pass);
bool mx_ckeck_user_name(char *table, char *name);
bool mx_find_name_in_tables(char *table, char *name);
bool mx_check_file(char *table, char *id, char **name, int flag);
void mx_free_list(t_list **list);
void mx_free_history(t_history *list);
void mx_free_table_list(t_table_list *list);
void mx_trim_for_size(t_list **list, char *size);
void mx_reply_forward(char *name_from, char *name_to, char *id, t_list **list);
char *mx_get_time(void);
char *mx_hash(char *salt, char *pass);
char *mx_get_img_path(char *name, char *another_name, int id, char **img_name);
int mx_folder(char *name);
int mx_get_id(char *name);
int mx_del_files(char *name);
int mx_drop_table(char *table);
int mx_delete_user(char *name);
int mx_create_table_users(void);
int mx_exe_command(char *command);
int mx_copy(char *old, char *new);
int mx_recv_new_mess(t_input *data);
int mx_get_type(char *name, int flag);
int mx_find_user_id(char *another_name);
int mx_delete_name(char *table, char *name);
int mx_change_log(char *name, char *new_name);
int mx_change_img(char *name, char *img_name);
int mx_change_pass(char *name, char *new_pass);
int mx_set_type(char *name, char *type, int flag);
int mx_del_history(char *name_from, char *name_to);
int mx_open_db(int flag, sqlite3 **db, char **err_msg);
int mx_add_new_user(char *name, char *pass, char *img_name);
int mx_del_message(char *name_from, char *name_to, char *id);
int mx_add_user_to_table(char *name, char *another_name, int flag);
int mx_exe(int flag, sqlite3 **db, char **command, char **err_msg);
int mx_del_user_from_table(char *name, char *another_name, int flag);
int mx_edit(char *name_from, char *name_to, char *new_mssg, char *id);

#endif
