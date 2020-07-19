#include "../inc/header.h"

/* open database database.db */
int mx_open_db(int flag, sqlite3 **db, char **err_msg) {
    flag = sqlite3_open("database.db", db);

    if (flag != SQLITE_OK) {
        printf("sqlite3_open: %s\n", sqlite3_errmsg(*db));
        sqlite3_free(*err_msg);
        sqlite3_close(*db);
        flag = 1;
    }
    return flag;
}
/* execute statement */
int mx_exe(int flag, sqlite3 **db, char **command, char **err_msg) {
    flag = sqlite3_exec(*db, *command, 0, 0, err_msg);

    if (flag != SQLITE_OK) {
        printf("sqlite3_exec: %s\n", sqlite3_errmsg(*db));
        sqlite3_free(*err_msg);
        sqlite3_close(*db);
        flag = 1;
    }
    return flag;
}
/* execute new command */
int mx_exe_command(char *command) {
    t_db data;

    data.command = command;
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        return 1;
    }
    if (mx_exe(data.flag, &data.db, &data.command, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        return 1;
    }
    sqlite3_close(data.db);
    return 0;
}
/* delete name in table */
int mx_delete_name(char *table, char *name) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.command = NULL;
    data.command = mx_super_join(data.command, "DELETE FROM ", 1);
    data.command = mx_super_join(data.command, table, 1);
    data.command = mx_super_join(data.command, " WHERE Name = ?;", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        mx_strdel(&(data.command));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    mx_strdel(&(data.command));
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}
/* drop table */
int mx_drop_table(char *table) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.command = NULL;
    data.command = mx_super_join("DROP TABLE ", table, 0);
    data.command = mx_super_join(data.command, ";", 1);
    if (mx_exe(data.flag, &data.db, &data.command, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return 1;
    }
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    return 0;
}
/* check name in table */
bool mx_ckeck_user_name(char *table, char *name) {
    if (!table || !name || mx_strcmp(name, "NULL") == 0)
        return false;
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return false;
    data.command = NULL;
    data.command = mx_super_join(data.command, "SELECT * FROM ", 1);
    data.command = mx_super_join(data.command, table, 1);
    data.command = mx_super_join(data.command, " WHERE Name = ?;", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return false;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    if (data.flag == SQLITE_ROW)
        return true;
    return false;
}
/* create user folder */
int mx_folder(char *name) {
    int result = 0;
    char *folder_name = NULL;

    folder_name = mx_super_join("./database/", name, 0);
    result = mkdir(folder_name, 0777);
    free(folder_name);
    folder_name = NULL;
    return result;
}
/* find id user in table Users */
int mx_find_user_id(char *another_name) {
    int result = 0;
    t_db data;

    data.command = "SELECT * FROM Users WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return result;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, another_name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 0);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return result;
}
/* get list of all tables */
static int mx_tables(void *NotUsed, int argc, char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        if (argv[i] && mx_strcmp(argv[i], "Users") != 0 && mx_strcmp(argv[i], "sqlite_sequence") != 0)
            mx_push_back(((t_list **)NotUsed), (void *)mx_strdup(argv[i]));
    return 0;
}
t_list *mx_get_tables_list(void) {
    t_db data;
    t_list *list = NULL;

    data.command = "SELECT name FROM sqlite_master WHERE type='table'";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.flag = sqlite3_exec(data.db, data.command, mx_tables, &list, &data.err_msg);
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}
/* free list */
void mx_free_list(t_list **list) {
    while (*list) {
        t_list *node = *list;

        *list = (*list)->next;
        if (node->data) {
            free(node->data);
            node->data = NULL;
        }
        node->next = NULL;
        free(node);
        node = NULL;
    }
}
/* find name in chats tables */
bool mx_find_name_in_tables(char *table, char *name) {
    char **two_names = mx_strsplit(table, '_');

    for (int i = 0; two_names[i]; i++)
        if (mx_strcmp(two_names[i], name) == 0) {
            mx_del_strarr(&two_names);
            return true;
        }
    mx_del_strarr(&two_names);
    return false;
}
/* get current time */
char *mx_get_time(void) {
    time_t rawtime;
    struct tm *timeinfo;
    char *time_str = NULL;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    time_str = asctime(timeinfo);
    if (time_str[mx_strlen(time_str) - 1] == '\n')
        time_str[mx_strlen(time_str) - 1] = '\0';
    return time_str;
}
/* get user id in Users */
int mx_get_id(char *name) {
    t_db data;
    int result = -1;

    data.command = "SELECT * FROM Users WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return -1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return -1;
    }
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 0);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return -1;
}
/* from one to another */
int mx_copy(char *old, char *new) {
    FILE *from = fopen(old, "rb");
    FILE *to = fopen(new, "wb");

    if (!to || !from) {
        if (from)
            fclose(from);
        if (to)
            fclose(to);
        return 1;
    }
    char send_buffer[1];
    int nb = fread(send_buffer, 1, 1, from);

    while (nb != 0) {
        fwrite(send_buffer, 1, 1, to);
        nb = fread(send_buffer, 1, 1, from);
    }
    fclose(from);
    fclose(to);
    return 0;
}
/* check file flag in table */
bool mx_check_file(char *table, char *id, char **name, int flag) {
    t_db data;
    int result = -1;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return false;
    data.command = NULL;
    data.command = mx_super_join("SELECT * FROM ", table, 0);
    data.command = mx_super_join(data.command, " WHERE Id = ?;", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_int(data.res, 1, mx_atoi(id));
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return false;
    }
    mx_strdel(&(data.command));
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 4);
        if (name && *name)
            *name = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        if (result == flag)
            return true;
        else
            return false;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return false;
}
/* strnsmp */
bool mx_part_cmp(char *data, char *part_name) {
    for (int i = 0; i < mx_strlen(part_name); i++) {
        if (part_name[i] == '\0')
            break;
        else if (data[i] != part_name[i])
            return false;
    }
    return true;
}
/* free history struct */
void mx_free_history(t_history *list) {
    if (!list)
        return;
    mx_strdel(&list->message);
    mx_strdel(&list->time);
    mx_strdel(&list->name);
    mx_strdel(&list->mssg_id);
    mx_strdel(&list->forward);
    mx_strdel(&list->file_name);
    mx_strdel(&list->flag);
    mx_strdel(&list->r_f_mssg);
    mx_strdel(&list->r_f_time);
}
/* trim list */
void mx_trim_for_size(t_list **list, char *size) {
    if (!size || !list || !*list)
        return ;
    int len = mx_list_size(*list);

    while (len > mx_atoi(size)) {
        mx_pop_front(list);
        len = mx_list_size(*list);
    }
}
/* del dir and file */
int mx_del_files(char *name) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") != 0 && mx_strcmp(entry->d_name, "..") != 0) {
            char *path = NULL;

            path = mx_super_join(name, "/", 0);
            path = mx_super_join(path, entry->d_name, 1);
            if (entry->d_type == DT_DIR) {
                result += mx_del_files(path);
                result += remove(path);
            }
            else
                result += remove(path);
            mx_strdel(&path);
        }
    }
    closedir(dir);
    return result;
}
/* free table list */
void mx_free_table_list(t_table_list *list) {
    if (!list)
        return;
    mx_strdel(&list->name);
    mx_strdel(&list->path_img);
    mx_strdel(&list->last_mssg);
    mx_strdel(&list->last_mssg_time);
}





/* move img */
int mx_change_img(char *name, char *img_name) {
    if (!name || !img_name)
        return 1;
    int result = 0;
    char *command = NULL;
    char *old = NULL;

    command = mx_super_join("./database/", name, 0);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, name, 1);
    command = mx_super_join(command, ".jpg", 1);
    old = mx_super_join("./", img_name, 0);
    remove(command);
    result += rename(old, command);
    mx_strdel(&old);
    mx_strdel(&command);
    return result;
}

/* create table Users */
int mx_create_table_users(void) {
    int result = 0;
    int dir = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "CREATE TABLE Users", 1);
    new_command = mx_super_join(new_command, "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
    new_command = mx_super_join(new_command, "Name TEXT NOT NULL, ", 1);
    new_command = mx_super_join(new_command, "Lan TEXT NOT NULL, ", 1);
    new_command = mx_super_join(new_command, "Theme INT, ", 1);
    new_command = mx_super_join(new_command, "Pass INT, ", 1);
    new_command = mx_super_join(new_command, "Img TEXT NOT NULL);", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    dir = mkdir("./database", 0700);
    if (!dir)
        result = 1;
    return result;
}

/* new user */
static void mx_rm_if_error(char *name) {
    char *img_path = NULL;

    img_path = mx_super_join("./", name, 0);
    img_path = mx_super_join(img_path, ".jpg", 1);
    remove(img_path);
    mx_strdel(&img_path);
}
static int mx_user_tables(char *name) {
    int result = 0;
    char *new_command = NULL;

    for (int i = 0; i < 3; i++) {
        new_command = mx_super_join(new_command, "CREATE TABLE ", 1);
        new_command = mx_super_join(new_command, name, 1);
        if (i == 0)
            new_command = mx_super_join(new_command, "_chats", 1);
        else if (i == 1)
            new_command = mx_super_join(new_command, "_friends", 1);
        else if (i == 2)
            new_command = mx_super_join(new_command, "_blacklist", 1);
        new_command = mx_super_join(new_command, "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
        new_command = mx_super_join(new_command, "Name TEXT NOT NULL, ", 1);
        new_command = mx_super_join(new_command, "Numb INT NOT NULL, ", 1);
        new_command = mx_super_join(new_command, "FOREIGN KEY (Numb) REFERENCES Users(Id));", 1);
        result += mx_exe_command(new_command);
        mx_strdel(&new_command);
    }
    return result;
}
int mx_add_new_user(char *name, char *pass, char *img_name) {
    if (!name || !pass || mx_ckeck_user_name("Users", name)) {
        mx_rm_if_error(name);
        return 1;
    }
    t_db data;

    data.command = "INSERT INTO Users(Name, Lan, Theme, Pass, Img) VALUES(?, ?, ?, ?, ?);";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(data.res, 2, 0);
        sqlite3_bind_int(data.res, 3, 0);
        sqlite3_bind_text(data.res, 4, pass, -1, SQLITE_TRANSIENT);
        char *img_path = NULL;

        img_path = mx_super_join("./database/", name, 0);
        img_path = mx_super_join(img_path, "/", 1);
        img_path = mx_super_join(img_path, name, 1);
        img_path = mx_super_join(img_path, ".jpg", 1);
        sqlite3_bind_text(data.res, 5, img_path, -1, SQLITE_TRANSIENT);
        mx_strdel(&img_path);
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE
        || mx_user_tables(name) != 0
        || mx_folder(name) != 0
        || mx_change_img(name , img_name) != 0) {
        mx_rm_if_error(name);
        return 1;
    }
    return 0;
}

/* add user to table */
static int mx_two_chats(char *name, char *another_name) {
    char *command = NULL;
    int result = 0;

    command = mx_super_join(command, "CREATE TABLE ", 1);
    command = mx_super_join(command, name, 1);
    command = mx_super_join(command, "_", 1);
    command = mx_super_join(command, another_name, 1);
    command = mx_super_join(command, "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
    command = mx_super_join(command, "Message TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "Time TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "Name TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "Reply TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "Forward TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "File TEXT NOT NULL, ", 1);
    command = mx_super_join(command, "Flag INT NOT NULL, ", 1);
    command = mx_super_join(command, "Fk INT NOT NULL, ", 1);
    command = mx_super_join(command, "FOREIGN KEY (Fk) REFERENCES Users(Id));", 1);
    result = mx_exe_command(command);
    mx_strdel(&command);
    return result;
}
static int mx_add_sub_folder(char *name, char *another_name, int flag) {
    if (flag != 0)
        return 0;
    int result = 0;
    char *folder_name = NULL;

    folder_name = mx_super_join("./database/", name, 0);
    folder_name = mx_super_join(folder_name, "/", 1);
    folder_name = mx_super_join(folder_name, another_name, 1);
    if (flag == 0)
        result = mkdir(folder_name, 0777);
    else if (flag == 1)
        result = remove(folder_name);
    mx_strdel(&folder_name);
    result += mx_two_chats(name, another_name);
    return result;
}
static bool mx_ckeck_user_in_table(char *name, char *another_name, int flag) {
    if (flag < 0 || flag > 2 || mx_strcmp(name, another_name) == 0)
        return true;
    char *table = NULL;

    if (flag == 0)
        table = mx_super_join(name, "_chats", 0);
    else if (flag == 1)
        table = mx_super_join(name, "_friends", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_blacklist", 0);
    if (mx_ckeck_user_name(table, another_name)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}
static bool mx_check_state(char *name, char *another_name, int flag) {
    char *table = NULL;

    if (flag == 1)
        table = mx_super_join(name, "_blacklist", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_friends", 0);
    if (mx_ckeck_user_name(table, another_name)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}
static int mx_change_state(char *name, char *another_name, int flag) {
    char *table = NULL;
    
    if (flag == 1)
        table = mx_super_join(name, "_blacklist", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_friends", 0);
    if (mx_check_state(name, another_name, flag) && mx_delete_name(table, another_name) == -1) {
        mx_strdel(&table);
        return 1;
    }
    mx_strdel(&table);
    return 0;
}
int mx_add_user_to_table(char *name, char *another_name, int flag) {
    if (!name || !another_name || mx_ckeck_user_in_table(name, another_name, flag))
        return 1;
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.command = NULL;
    data.command = mx_super_join(data.command, "INSERT INTO ", 1);
    data.command = mx_super_join(data.command, name, 1);
    if (flag == 0)
        data.command = mx_super_join(data.command, "_chats", 1);
    else if (flag == 1)
        data.command = mx_super_join(data.command, "_friends", 1);
    else if (flag == 2)
        data.command = mx_super_join(data.command, "_blacklist", 1);
    data.command = mx_super_join(data.command, "(Name, Numb) ", 1);
    data.command = mx_super_join(data.command, "VALUES(?, ?);", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        sqlite3_bind_text(data.res, 1, another_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(data.res, 2, mx_find_user_id(another_name));
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    if (data.flag != SQLITE_DONE ||
        mx_change_state(name, another_name, flag) != 0 ||
        mx_add_sub_folder(name, another_name, flag) != 0)
        return 1;
    return 0;
}

/* delete user */
static int mx_delete_in_other(char *name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_get_substr_index((char *)node->data, "_blacklist") > 0
            || mx_get_substr_index((char *)node->data, "_friends") > 0
            || mx_get_substr_index((char *)node->data, "_chats") > 0
            || mx_strcmp((char *)node->data, "Users") == 0)
                result += mx_delete_name((char *)node->data, name);
        else if (mx_find_name_in_tables((char *)node->data, name))
            result += mx_drop_table((char *)node->data);
    }
    mx_free_list(&list);
    return result;
}
static int mx_delete_all(char *name, char *user, int flag) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") != 0 && mx_strcmp(entry->d_name, "..") != 0) {
            char *path = NULL;

            path = mx_super_join(name, "/", 0);
            path = mx_super_join(path, entry->d_name, 1);
            if (entry->d_type != DT_DIR && flag == 1)
                result += remove(path);
            else if (entry->d_type == DT_DIR) {
                if (mx_strcmp(entry->d_name, user) == 0)
                    result += mx_delete_all(path, user, 1);
                else
                    result += mx_delete_all(path, user, flag);
                if (flag == 1 || mx_strcmp(entry->d_name, user) == 0)
                    result += remove(path);
            }
            mx_strdel(&path);
        }
    }
    closedir(dir);
    return result;
}
int mx_delete_user(char *name) {
    if (!name || !mx_ckeck_user_name("Users", name))
        return 1;
    int result = 0;
    char *new_command = NULL;

    for (int i = 0; i < 3; i++) {
        if (i == 0)
            new_command = mx_super_join(name, "_chats", 0);
        else if (i == 1)
            new_command = mx_super_join(name, "_friends", 0);
        else if (i == 2)
            new_command = mx_super_join(name, "_blacklist", 0);
        result += mx_drop_table(new_command);
        mx_strdel(&new_command);
    }
    result += mx_delete_name("Users", name);
    if (mx_delete_all("./database", name, 0) != 0 || mx_delete_in_other(name) != 0)
        return 1;
    return result;
}

/* add new message */
static void mx_del_after(char *name, char * mssg) {
    char **arr = mx_strsplit(mssg, '.');
    char *path = NULL;
    
    path = mx_super_join("./", name, 0);
    path = mx_super_join(path, ".", 1);
    path = mx_super_join(path, arr[mx_arr_size(arr) - 1], 1);
    remove(path);
    mx_strdel(&path);
    mx_del_strarr(&arr);
}
static bool mx_check_blacklist(char *name_from, char *name_to) {
    char *table = mx_super_join(name_to, "_blacklist", 0);

    if (mx_ckeck_user_name(table, name_from)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}
static int mx_whos_mssg(char *name_from, char *name_to, char *who) {
    int result = 0;
    char *command = NULL;

    command = mx_super_join("UPDATE ", name_from, 0);
    command = mx_super_join(command, "_", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, " SET Name = '", 1);
    command = mx_super_join(command, who, 1);
    command = mx_super_join(command, "' WHERE Name = 'NULL';", 1);
    result += mx_exe_command(command);
    mx_strdel(&command);
    return result;
}
static int mx_move_file(char *name_from, char *name_to, char *message, char *file_name) {
    int result = 0;
    char *command = NULL;
    char *old = NULL;

    command = mx_super_join("./database/", name_from, 0);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, mx_get_time(), 1);
    char **format = mx_strsplit(message, '.');

    old = mx_super_join("./", file_name, 0);
    if (mx_arr_size(format) == 2) {
        old = mx_super_join(old, ".", 1);
        old = mx_super_join(old, format[mx_arr_size(format) - 1], 1);
    }
    result = mx_copy(old, command);
    mx_strdel(&old);
    mx_strdel(&command);
    mx_del_strarr(&format);
    return result;
}
static char *mx_other_mssg(char *name_from, char *name_to, char *message, int flag) {
    char *path = NULL;

    if (flag == 0)
        path = mx_strdup(message);
    if (flag == 1) {
        path = mx_super_join("./database/", name_from, 0);
        path = mx_super_join(path, "/", 1);
        path = mx_super_join(path, name_to, 1);
        path = mx_super_join(path, "/", 1);
        path = mx_super_join(path, mx_get_time(), 1);
    }
    else if (flag == 2)
        path = mx_super_join("./source/sticker_gif/", message, 0);
    return path;
}
static int mx_insert_mssg(t_input *node) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.command = NULL;
    data.command = mx_super_join("INSERT INTO ", node->name_from, 0);
    data.command = mx_super_join(data.command, "_", 1);
    data.command = mx_super_join(data.command, node->name_to, 1);
    data.command = mx_super_join(data.command, "(Message, Time, Name, Reply, Forward, File, Flag, Fk) VALUES(?, ?, ?, ?, ?, ?, ?, ?);", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        char *form = mx_other_mssg(node->name_from, node->name_to, node->message, node->flag);

        sqlite3_bind_text(data.res, 1, form, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 2, mx_get_time(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 3, "NULL", -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 4, node->reply, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 5, node->forward, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 6, node->file_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(data.res, 7, node->flag);
        sqlite3_bind_int(data.res, 8, mx_get_id(node->name_to));
        mx_strdel(&form);
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return 1;
    }
    mx_strdel(&(data.command));
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}
static bool mx_first_message(char *name_from, char *name_to) {
    int flag = 1;
    t_list *list = mx_get_tables_list();
    char *table = NULL;

    table = mx_super_join(name_from, "_", 0);
    table = mx_super_join(table, name_to, 1);
    for (t_list *node = list; node; node = node->next)
        if (mx_strcmp((char *)node->data, table) == 0)
            flag = 0;
    mx_strdel(&table);
    mx_free_list(&list);
    return flag;
}
int mx_recv_new_mess(t_input *data) {
    if (!data->name_from
        || !data->name_to
        || (data->flag < 0 && data->flag > 2)
        || !data->message
        || mx_check_blacklist(data->name_from, data->name_to))
        return 1;
    int result = 0;

    if (mx_first_message(data->name_from, data->name_to))
        result += mx_add_user_to_table(data->name_from, data->name_to, 0);
    if (mx_first_message(data->name_to, data->name_from))
        result += mx_add_user_to_table(data->name_to, data->name_from, 0);
    result += mx_insert_mssg(data);
    result += mx_whos_mssg(data->name_from, data->name_to, data->name_from);
    char *shift = NULL;

    shift = data->name_from;
    data->name_from = data->name_to;
    data->name_to = shift;
    result += mx_insert_mssg(data);
    result += mx_whos_mssg(data->name_from, data->name_to, data->name_to);

    if (data->flag == 1) {
        result += mx_move_file(data->name_from, data->name_to, data->message, data->name_to);
        result += mx_move_file(data->name_to, data->name_from, data->message, data->name_to);
        mx_del_after(data->name_to, data->file_name);
    }
    return result;
}

/* send history back */
static int mx_history(void *NotUsed, int argc, char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i += 9) {
        t_history *node = (t_history *)malloc(sizeof(t_history));

        node->id = mx_atoi(argv[0]);
        node->message = mx_strdup(argv[1]);
        node->time = mx_strdup(argv[2]);
        node->name = mx_strdup(argv[3]);
        node->mssg_id = mx_strdup(argv[4]);
        node->forward = mx_strdup(argv[5]);
        node->file_name = mx_strdup(argv[6]);
        node->flag = mx_strdup(argv[7]);
        node->r_f_mssg = NULL;
        node->r_f_time = NULL;
        mx_push_back(((t_list **)NotUsed), (void *)node);
    }
    return 0;
}
t_list *mx_history_back(char *name_from, char *name_to, char *size) {
    if (!name_from || !name_to)
        return NULL;
    t_db data;
    t_list *list = NULL;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.command = NULL;
    data.command = mx_super_join(data.command, "SELECT * FROM ", 1);
    data.command = mx_super_join(data.command, name_from, 1);
    data.command = mx_super_join(data.command, "_", 1);
    data.command = mx_super_join(data.command, name_to, 1);
    if (size) {
        data.command = mx_super_join(data.command, " ORDER BY Id DESC LIMIT ", 1);
        data.command = mx_super_join(data.command, size, 1);
    }
    data.flag = sqlite3_exec(data.db, data.command, mx_history, &list, &data.err_msg);
    mx_strdel(&(data.command));
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}

/* send table list */
static t_table_list *mx_create_table_list(char *name) {
    t_table_list *node = (t_table_list *)malloc(sizeof(t_table_list));
    char *path = NULL;

    node->name = mx_strdup(name);
    path = mx_super_join("./database/", name, 0);
    path = mx_super_join(path, "/", 1);
    path = mx_super_join(path, name, 1);
    path = mx_super_join(path, ".jpg", 1);
    node->path_img = mx_strdup(path);
    node->last_mssg = NULL;
    node->last_mssg_time = NULL;
    mx_strdel(&path);
    return node;
}
static int mx_list_back(void *NotUsed, int argc, char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        mx_push_back(((t_list **)NotUsed), (void *)mx_create_table_list(argv[0]));
    return 0;
}
static void mx_find_last_mssg(char *table, char **message, char **time) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return ;
    data.command = NULL;
    data.command = mx_super_join("SELECT * FROM ", table, 0);
    data.command = mx_super_join(data.command, " ORDER BY Id DESC LIMIT 1;", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag != SQLITE_OK) {
        mx_strdel(&(data.command));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return ;
    }
    mx_strdel(&(data.command));
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        *message = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        *time = mx_strdup((char *)sqlite3_column_text(data.res, 2));
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
}
static void mx_add_mssg_time(t_list **list, char *name) {
    for (t_list *node = *list; node; node = node->next) {
        char *table_name = NULL;

        table_name = mx_super_join(name, "_", 0);
        table_name = mx_super_join(table_name, ((t_table_list *)node->data)->name, 1);
        mx_find_last_mssg(table_name, &((t_table_list *)node->data)->last_mssg, &((t_table_list *)node->data)->last_mssg_time);
        mx_strdel(&table_name);
    }
}
t_list *mx_send_list_back(char *name, int flag) {
    if (!name || (flag != 0 && flag != 1))
        return NULL;
    t_db data;
    t_list *list = NULL;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.command = NULL;
    data.command = mx_super_join(data.command, "SELECT Name FROM ", 1);
    data.command = mx_super_join(data.command, name, 1);
    if (flag == 0)
        data.command = mx_super_join(data.command, "_chats;", 1);
    else if (flag == 1)
        data.command = mx_super_join(data.command, "_friends;", 1);
    else if (flag == 2)
        data.command = mx_super_join(data.command, "_blacklist;", 1);
    data.flag = sqlite3_exec(data.db, data.command, mx_list_back, &list, &data.err_msg);
    mx_strdel(&(data.command));
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    if (flag == 1)
        mx_add_mssg_time(&list, name);
    return list;
}

/* delete history */
static int mx_del_other_hist(char *name_from, char *name_to) {
    int result = 0;
    char *cmd = NULL;

    result += mx_del_user_from_table(name_from, name_to, 0);
    cmd = mx_super_join(name_from, "_", 0);
    cmd = mx_super_join(cmd, name_to, 1);
    result += mx_drop_table(cmd);
    mx_strdel(&cmd);
    cmd = mx_super_join("./database/", name_from, 0);
    cmd = mx_super_join(cmd, "/", 1);
    cmd = mx_super_join(cmd, name_to, 1);
    result += remove(cmd);
    mx_strdel(&cmd);
    return result;
}
int mx_del_history(char *name_from, char *name_to) {
    if (!name_from || !name_to)
        return 1;
    int result = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name_from, 1);
    new_command = mx_super_join(new_command, "_", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    new_command = mx_super_join(new_command, ";", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    new_command = mx_super_join("./database/", name_from, 0);
    new_command = mx_super_join(new_command, "/", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    result += mx_del_files(new_command);
    mx_strdel(&new_command);
    result += mx_del_other_hist(name_from, name_to);
    return result;
}

/* delete message */
int mx_del_message(char *name_from, char *name_to, char *id) {
    if (!name_to || !name_from || !id)
        return 1;
    int result = 0;
    char *new_command = NULL;
    char *name = NULL;

    new_command = mx_super_join(name_from, "_", 0);
    new_command = mx_super_join(new_command, name_to, 1);
    if (mx_check_file(new_command, id, &name, 1)) {
        result += remove(name);
        mx_strdel(&name);
    }
    mx_strdel(&new_command);
    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name_from, 1);
    new_command = mx_super_join(new_command, "_", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    new_command = mx_super_join(new_command, " WHERE Id = ", 1);
    new_command = mx_super_join(new_command, id, 1);
    new_command = mx_super_join(new_command, ";", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    return result;
}

/* edit message */
int mx_edit(char *name_from, char *name_to, char *new_mssg, char *id) {
    if (!name_from || !name_to || !new_mssg || !id)
        return 1;
    char *table = NULL;

    table = mx_super_join(name_from, "_", 0);
    table = mx_super_join(table, name_to, 1);
    if (mx_check_file(table, id, NULL, 1) || mx_check_file(table, id, NULL, 2)) {
        mx_strdel(&table);
        return 1;
    }
    mx_strdel(&table);
    char *command = NULL;
    int result = 0;

    command = mx_super_join("UPDATE ", name_from, 0);
    command = mx_super_join(command, "_", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, " SET Message = '", 1);
    command = mx_super_join(command, new_mssg, 1);
    command = mx_super_join(command, "', Time = ", 1);
    command = mx_super_join(command, "'edit ", 1);
    command = mx_super_join(command, mx_get_time(), 1);
    command = mx_super_join(command, "' WHERE Id = ", 1);
    command = mx_super_join(command, id, 1);
    command = mx_super_join(command, ";", 1);
    result += mx_exe_command(command);
    mx_strdel(&command);
    return result;
}

/* change log */
static int mx_in_other_tables(char *name, char *new_name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_ckeck_user_name((char *)node->data, name)) {
            char *command = NULL;

            command = mx_super_join("UPDATE ", (char *)node->data, 0);
            command = mx_super_join(command, " SET Name = '", 1);
            command = mx_super_join(command, new_name, 1);
            command = mx_super_join(command, "' WHERE Name = '", 1);
            command = mx_super_join(command, name, 1);
            command = mx_super_join(command, "';", 1);
            result += mx_exe_command(command);
            mx_strdel(&command);
        }
    }
    mx_free_list(&list);
    return result;
}
static int mx_change_other_folders(char *name, char *user, char *new_user) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") != 0 && mx_strcmp(entry->d_name, "..") != 0) {
            char *path = NULL;

            path = mx_super_join(name, "/", 0);
            path = mx_super_join(path, entry->d_name, 1);
            if (entry->d_type == DT_DIR) {
                result += mx_change_other_folders(path, user, new_user);
                if (mx_strcmp(user, entry->d_name) == 0) {
                    char *new = NULL;

                    new = mx_super_join(name, "/", 0);
                    new = mx_super_join(new, new_user, 1);
                    result += rename(path, new);
                    mx_strdel(&new);
                }
            }
            mx_strdel(&path);
        }
    }
    closedir(dir);
    return result;
}
static int mx_change_user_table(char *name, char *new_name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_find_name_in_tables((char *)node->data, name)) {
            char *change = mx_replace_substr((char *)node->data, name, new_name);
            char *new_command = NULL;

            new_command = mx_super_join("ALTER TABLE ", (char *)node->data, 0);
            new_command = mx_super_join(new_command, " RENAME TO ", 1);
            new_command = mx_super_join(new_command, change, 3);
            new_command = mx_super_join(new_command, ";", 1);
            result += mx_exe_command(new_command);
            mx_strdel(&new_command);
        }
    }
    mx_free_list(&list);
    return result;
}
static int mx_change_path_table(char *new_user, char *new_path) {
    t_db data;

    data.command = "UPDATE Users SET Img = ? WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        sqlite3_bind_text(data.res, 1, new_path, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 2, new_user, -1, SQLITE_TRANSIENT);
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}
static int mx_change_img_path(char *user, char *new_user) {
    int result = 0;
    char *old = NULL;
    char *new = NULL;

    old = mx_super_join("./database/", user, 0);
    old = mx_super_join(old, "/", 1);
    old = mx_super_join(old, user, 1);
    old = mx_super_join(old, ".jpg", 1);
    new = mx_super_join("./database/", user, 0);
    new = mx_super_join(new, "/", 1);
    new = mx_super_join(new, new_user, 1);
    new = mx_super_join(new, ".jpg", 1);
    result += rename(old, new);
    result += mx_change_path_table(new_user, new);
    mx_strdel(&old);
    mx_strdel(&new);
    return result;
}
int mx_change_log(char *name, char *new_name) {
    if (!name
        || !new_name
        || isdigit(new_name[0]))
        return 1;
    t_db data;

    if (mx_change_user_table(name, new_name) != 0)
        return 1;
    data.command = "UPDATE Users SET Name = ? WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        sqlite3_bind_text(data.res, 1, new_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 2, name, -1, SQLITE_TRANSIENT);
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE
        || mx_change_img_path(name, new_name) != 0
        || mx_change_other_folders("./database", name, new_name) != 0
        || mx_in_other_tables(name, new_name) != 0) {
        return 1;
    }
    return 0;
}

/* change pass */
int mx_change_pass(char *name, char *new_pass) {
    if (!name || !new_pass ||!mx_ckeck_user_name("Users", name))
        return 1;
    t_db data;

    data.command = "UPDATE Users SET Pass = ? WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK) {
        sqlite3_bind_text(data.res, 1, new_pass, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data.res, 2, name, -1, SQLITE_TRANSIENT);
    }
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return 1;
    }
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}

/* reply forward */
void mx_reply_forward(char *name_from, char *name_to, char *id, t_list **list) {
    if (!name_to || !name_from || !id || !*list)
        return ;
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return ;
    data.command = NULL;
    data.command = mx_super_join("SELECT * FROM ", name_from, 0);
    data.command = mx_super_join(data.command, "_", 1);
    data.command = mx_super_join(data.command, name_to, 1);
    data.command = mx_super_join(data.command, " WHERE Id = ", 1);
    data.command = mx_super_join(data.command, id, 1);
    data.command = mx_super_join(data.command, ";", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag != SQLITE_OK) {
        mx_strdel(&(data.command));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return ;
    }
    data.flag = sqlite3_step(data.res);
    mx_strdel(&(data.command));
    if (data.flag == SQLITE_ROW) {
        ((t_history *)(*list)->data)->r_f_mssg = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        ((t_history *)(*list)->data)->r_f_time = mx_strdup((char *)sqlite3_column_text(data.res, 2));
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
}

/* check user pass */
bool mx_check_user_pass(char *name, char *pass) {
    if (!name || !pass || !mx_ckeck_user_name("Users", name))
        return false;
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return false;
    data.command = "SELECT * FROM Users WHERE Name = ?";
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return false;
    }
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW)
        if (mx_strcmp((char *)sqlite3_column_text(data.res, 2), pass) == 0) {
            sqlite3_finalize(data.res);
            sqlite3_close(data.db);
            return true;
        }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return false;
}

/* user search */
static int mx_users(void *NotUsed, int argc, char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        mx_push_back(((t_list **)NotUsed), (void *)mx_strdup(argv[i]));
    return 0;
}
static t_list *mx_get_user_list(void) {
    t_db data;
    t_list *list = NULL;

    data.command = "SELECT Name FROM Users";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.flag = sqlite3_exec(data.db, data.command, mx_users, &list, &data.err_msg);
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}
t_list *mx_user_search(char *part_name, char *size) {
    if (!part_name)
        return NULL;
    t_list *list = mx_get_user_list();
    t_list *true_list = NULL;

    for (t_list *node = list; node; node = node->next) {
        if (mx_part_cmp((char *)node->data, part_name)) {
            t_table_list *transfer = (t_table_list *)malloc(sizeof(t_table_list));

            transfer->name = mx_strdup((char *)node->data);
            transfer->path_img = mx_super_join("./database/", (char *)node->data, 0);
            transfer->path_img = mx_super_join(transfer->path_img, "/", 1);
            transfer->path_img = mx_super_join(transfer->path_img, (char *)node->data, 1);
            transfer->path_img = mx_super_join(transfer->path_img, ".jpg", 1);
            transfer->last_mssg = NULL;
            transfer->last_mssg_time = NULL;
            mx_push_back(&true_list, transfer);
        }
    }
    mx_free_list(&list);
    mx_trim_for_size(&true_list, size);
    return true_list;
}

/* message search */
static void mx_copy_struct(t_history **first, t_history *second) {
    *first = (t_history *)malloc(sizeof(t_history));
    (*first)->id = second->id;
    (*first)->message = mx_strdup(second->message);
    (*first)->time = mx_strdup(second->time);
    (*first)->name = mx_strdup(second->name);
    (*first)->mssg_id = mx_strdup(second->mssg_id);
    (*first)->forward = mx_strdup(second->forward);
    (*first)->file_name = mx_strdup(second->file_name);
    (*first)->flag = mx_strdup(second->flag);
    (*first)->r_f_mssg = NULL;
    (*first)->r_f_time = NULL;
}
t_list *mx_mssg_search(char *name, char *another_name, char *part_mssg, char *size) {
    if (!name || !another_name || !part_mssg)
        return NULL;
    t_list *list = mx_history_back(name, another_name, NULL);
    t_list *true_list = NULL;

    for (t_list *node = list; node; node = node->next) {
        if (mx_part_cmp(((t_history *)node->data)->message, part_mssg)) {
            t_history *copy = NULL;

            mx_copy_struct(&copy, (t_history *)node->data);
            mx_push_back(&true_list, (void *)copy);
        }
        mx_free_history((t_history *)node->data);
    }
    mx_free_list(&list);
    mx_trim_for_size(&true_list, size);
    return true_list;
}

/* hash pass */
char *mx_hash(char *salt, char *pass) {
    if (!salt || !pass)
        return NULL;
    char *hash = NULL;
    char *full = mx_super_join(salt, pass, 0);
    unsigned char md[64];
    SHA512_CTX ctx;

    SHA512_Init(&ctx);
    SHA512_Update(&ctx, full, mx_strlen(full));
    SHA512_Final(md, &ctx);
    mx_strdel(&full);
    for (int i = 0; i < 64; i++) {
        if ((int)md[i] >= 0 && (int)md[i] <= 15) {
            hash = mx_super_join(hash, "0", 1);
            if ((int)md[i] == 0)
                hash = mx_super_join(hash, "0", 1);
        }
        char *add = mx_nbr_to_hex((unsigned long)md[i]);

        hash = mx_super_join(hash, add, 1);
        mx_strdel(&add);
    }
    hash[128] = '\0';
    return hash;
}

/* set theme or lan */
int mx_set_type(char *name, char *type, int flag) {
    if (!name || !type || (flag != 0 && flag != 1))
        return 1;
    int result = 0;
    char *command = NULL;

    if (flag == 0)
        command = mx_super_join("UPDATE Users SET Lan = '", type, 0);
    else if (flag == 1)
        command = mx_super_join("UPDATE Users SET Theme = '", type, 0);
    command = mx_super_join(command, "' WHERE Name = '", 1);
    command = mx_super_join(command, name, 1);
    command = mx_super_join(command, "';", 1);
    result += mx_exe_command(command);
    mx_strdel(&command);
    return result;
}

/* get theme or lan */
int mx_get_type(char *name, int flag) {
    t_db data;
    int result = -1;

    if (flag == 0)
        data.command = "SELECT Lan FROM Users WHERE Name = ?";
    else if (flag == 1)
        data.command = "SELECT Theme FROM Users WHERE Name = ?";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return -1;
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_text(data.res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return -1;
    }
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 0);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return -1;
}

/* down load file */
char *mx_get_img_path(char *name, char *another_name, int id, char **img_name) {
    t_db data;
    char *path = NULL;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return path;
    data.command = NULL;
    data.command = mx_super_join("SELECT * FROM ", name, 0);
    data.command = mx_super_join(data.command, "_", 1);
    data.command = mx_super_join(data.command, another_name, 1);
    data.command = mx_super_join(data.command, " WHERE Id = ?", 1);
    data.flag = sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (data.flag == SQLITE_OK)
        sqlite3_bind_int(data.res, 1, id);
    else {
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        mx_strdel(&data.command);
        return path;
    }
    mx_strdel(&data.command);
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        path = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        *img_name = mx_strdup((char *)sqlite3_column_text(data.res, 6));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return path;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return path; 
}

/* delete from friends/blacklist */
int mx_del_user_from_table(char *name, char *another_name, int flag) {
    if (!name || !another_name)
        return 1;
    int result = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name, 1);
    if (flag == 0)
        new_command = mx_super_join(new_command, "_chats", 1);
    else if (flag == 1)
        new_command = mx_super_join(new_command, "_friends", 1);
    else if (flag == 2)
        new_command = mx_super_join(new_command, "_blacklist", 1);
    new_command = mx_super_join(new_command, " WHERE Name = '", 1);
    new_command = mx_super_join(new_command, another_name, 1);
    new_command = mx_super_join(new_command, "';", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    return result;        
}
