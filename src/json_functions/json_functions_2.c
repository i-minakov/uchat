#include "../../inc/header.h"

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
