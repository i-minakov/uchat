#include "../../inc/header.h"

static int mx_json_add_object(cJSON **cmd_name,
                              char *str1, char *str2) {
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

static void mx_json_add_arr_adt(cJSON **argument,
                                char **position, int i) {
    *argument = cJSON_CreateObject();
    *position = mx_itoa(i + 1);
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
        mx_json_add_arr_adt(&argument, &position, i);
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
