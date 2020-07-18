#ifndef JSON_FUN_H
#define JSON_FUN_H

#include "cJSON.h"

bool mx_check_json_cmd(char *str, char *command, char *cmp);
char *mx_request(char *command_name, char **arr);
char *mx_get_value(char *str, char *parametr);
char **mx_get_arr(char *str);

#endif
