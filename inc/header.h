#ifndef HEADER_H
#define HEADER_H

#include <pwd.h>
#include <grp.h>
#include <poll.h>
#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/uio.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <ctype.h>

#include "../libmx/inc/libmx.h"
#include "json_functions.h"
#include "database.h"
#include "ssl.h"
#include "uchat.h"

#define FLAG 10
#define TIMER 1000
#define SIZE_SEND 1027
#define FILE_SIZE 262144000
#define SIZE_SEND_LESS 1024

// Client
char *mx_right_path(t_info **info, t_files *files);
void mx_client_send(t_client *client);
void mx_sort_mssg(t_list **list, int flag);
void mx_send_command(char *json, t_client *client);
void mx_recv_len_theme(char ch[], t_client *client);
void mx_client_recv_file(char ch[], t_client *client);
void mx_recv_list(char ch[], t_info **info, t_files *files, t_client *client);
void mx_recv_list_files(char ch[], t_info **info, t_files *files);
void *mx_files(void *client_pointer);
void *mx_client_read(void *client_pointer);
int mx_monthcmp(char *month1, char *month2);
int mx_intcmp(char *str1, char *str2);
int mx_client(int argc, char *argv[]);

// Server
void mx_choose(t_node *node, char **json);
void mx_not_mutex(t_node **node, char **json);
void mx_exe_request(t_node **node, char **json);
void mx_send_history_list(t_node **node, char *name);
void mx_send_answer_type(t_node **node, int type, int flag);
void mx_del_client(t_way **list, t_node **node, void *data);
void mx_send_answer_list(t_node **node, t_list *list, int hist_flag, char *cmd);
void *mx_server_files(void *data);
void *mx_server_handel(void *data);
int mx_server(int argc, char *argv[]);

// help
void mx_del_if_exist(char *name);
void mx_del_file(FILE *file, char **size, char **name);
void mx_check_file_size(FILE *file, char **size, char **name);
char *mx_add_char(char *str, char c);
char *mx_super_join(char *src1, char *src2, int fl);
char **mx_copy_arr(char **s);
char **mx_arrjoin(char **arr, char *str);
bool mx_for_file(char *json);
void mx_free_node(t_way **list);
void mx_del_list(t_list **list, int flag);
void mx_unset_file_node(t_way **list);
void mx_replace(char **old, char *new);
void mx_static_read(char ch[], char **str);
void mx_push_file_way(t_way **list, void *data);
void mx_push_back_t_way(t_way **list, void *data);
void mx_bites_str(SSL *ssl, char *json, char ch1);
void mx_file_bites(FILE *file, SSL *ssl, char ch1, char ch2);
void mx_file_format(char **arr, SSL *ssl, char ch1, char ch2);
void mx_file_size_close(SSL *ssl, char *str, char ch1, char ch2);
void *mx_mom(void *restrict dst, const void *restrict src, size_t n, size_t i);
int mx_arr_size(char **arr);

int chat_screen(t_main **gtk);

#endif
