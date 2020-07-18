#include "header.h"

static int mx_json_add_object(cJSON **cmd_name, char *str1, char *str2) {
    cJSON *check = NULL;

    if (str2)
        check = cJSON_AddStringToObject(*cmd_name, str1, str2);
    else
        check = cJSON_AddStringToObject(*cmd_name, str1, "NULL");
    if (check == NULL) {
        cJSON_Delete(*cmd_name);
        return 1;
    }
    return 0;
}
static int mx_json_add_arr(cJSON **cmd_name, char **arr) {
    cJSON *argv = NULL;
    cJSON *argument = NULL;
    char *position = NULL;

    argv = cJSON_AddArrayToObject(*cmd_name, "argv");
    if (argv == NULL) {
        cJSON_Delete(*cmd_name);
        return 1;
    }
    for (int i = 0; arr[i]; i++) {
        argument = cJSON_CreateObject();
        position = mx_itoa(i + 1);
        if (cJSON_AddStringToObject(argument, position, arr[i]) == NULL) {
            cJSON_Delete(*cmd_name);
            mx_strdel(&position);
            return 1;
        }
        cJSON_AddItemToArray(argv, argument);
        mx_strdel(&position);
    }
    return 0;
}
char *mx_request(char *command_name, char **arr) {
    if (!command_name || !arr || !*arr)
        return NULL;
    char *str = NULL;
    cJSON *cmd_name = cJSON_CreateObject();

    if (mx_json_add_object(&cmd_name, "command", command_name) == 1)
        return str;
    if (mx_json_add_arr(&cmd_name, arr) == 1)
        return str;
    str = cJSON_Print(cmd_name);
    cJSON_Delete(cmd_name);
    return str;
}

bool mx_check_json_cmd(char *str, char *command, char *cmp) {
    char *finder = mx_get_value(str, command);

    if (finder && mx_strcmp(finder, cmp) == 0) {
        mx_strdel(&finder);
        return true;
    }
    mx_strdel(&finder);
    return false;
}

static char *mx_open_quotes(char *old_cmd) {
    char *new_cmd = mx_strnew(mx_strlen(old_cmd) - 2);

    for (int i = 0; i < mx_strlen(old_cmd) - 2; i++)
        new_cmd[i] = old_cmd[i + 1];
    free(old_cmd);
    old_cmd = NULL;
    return new_cmd;
}
char *mx_get_value(char *str, char *parametr) {
    cJSON *name = NULL;
    cJSON *cmd_name = cJSON_Parse(str);
    char *command = NULL;

    if (cmd_name == NULL) {
        cJSON_Delete(cmd_name);
        return command;
    }
    name = cJSON_GetObjectItemCaseSensitive(cmd_name, parametr);
    if (!cJSON_IsString(name) && (name->valuestring == NULL)) {
        cJSON_Delete(cmd_name);
        return command;
    }
    command = cJSON_Print(name);
    command = mx_open_quotes(command);
    cJSON_Delete(cmd_name);
    return command;
}

static void mx_json_arr(cJSON *cmd_name, char ***arr) {
    cJSON *argv = cJSON_GetObjectItemCaseSensitive(cmd_name, "argv");
    cJSON *line = NULL;
    cJSON *str = NULL;
    char *str_itoa = NULL;
    int index = 0;

    cJSON_ArrayForEach(line, argv) {
        str_itoa = mx_itoa(index + 1);
        str = cJSON_GetObjectItemCaseSensitive(line, str_itoa);
        *arr = mx_arrjoin(*arr, str->valuestring);
        index += 1;
        mx_strdel(&str_itoa);
    }
}
char **mx_get_arr(char *str) {
    cJSON *cmd_name = cJSON_Parse(str);
    char **arr = NULL;

    if (cmd_name == NULL) {
        cJSON_Delete(cmd_name);
        return arr;
    }
    mx_json_arr(cmd_name, &arr);
    cJSON_Delete(cmd_name);
    return arr;
}
