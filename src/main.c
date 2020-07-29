#include "../inc/header.h"

int main(int argc, char *argv[]) {
    if (!strcmp(argv[1], "server"))
        return mx_server(argc, argv);
    else if (!strcmp(argv[1], "client"))
        return mx_client(argc, argv);
    else if (!strcmp(argv[1], "chat"))
        return interface();
    return 0;
}

/*static void mx_print_list(t_list *list, char *name, char *another_name) {
    for (t_list *node = list; node; node = node->next) {
        printf("%d\t", ((t_history *)node->data)->id);
        printf("%s\t", ((t_history *)node->data)->message);
        printf("%s\t", ((t_history *)node->data)->time);
        printf("%s\t", ((t_history *)node->data)->name);
        printf("%s\t", ((t_history *)node->data)->mssg_id ? ((t_history *)node->data)->mssg_id : "NULL");
        printf("%s\t", ((t_history *)node->data)->forward ? ((t_history *)node->data)->forward : "NULL");
        printf("%s\t", ((t_history *)node->data)->flag);
        printf("%s\n", ((t_history *)node->data)->file_name ? ((t_history *)node->data)->file_name : "NULL");
        if (mx_strcmp(((t_history *)node->data)->mssg_id, "NULL") != 0 && mx_strcmp(((t_history *)node->data)->forward, "NULL") == 0) {
            mx_reply_forward(name, another_name, ((t_history *)node->data)->mssg_id, &node);
            printf("\tReply to the message id %s => ", ((t_history *)node->data)->mssg_id);
            printf("%s\t", ((t_history *)node->data)->r_f_mssg ? ((t_history *)node->data)->r_f_mssg : "NULL");
            printf("%s\n", ((t_history *)node->data)->r_f_time ? ((t_history *)node->data)->r_f_time : "NULL");
        }
        else if (mx_strcmp(((t_history *)node->data)->forward, "NULL") != 0) {
            mx_reply_forward(name, ((t_history *)node->data)->forward, ((t_history *)node->data)->mssg_id, &node);
            printf("\tForward from %s to the message id %s => ", ((t_history *)node->data)->forward, ((t_history *)node->data)->mssg_id);
            printf("%s\t", ((t_history *)node->data)->r_f_mssg ? ((t_history *)node->data)->r_f_mssg : "NULL");
            printf("%s\n", ((t_history *)node->data)->r_f_time ? ((t_history *)node->data)->r_f_time : "NULL");
        }
    }
}
int main(int argc, char *argv[]) {
    int result = 0;

    if (argc == 2 && mx_strcmp(argv[1], "1") == 0)
        result = mx_create_table_users();
    else if (argc == 5 && mx_strcmp(argv[1], "2") == 0)
        result = mx_add_new_user(argv[2], argv[3], argv[4]);
    else if (argc == 5 && mx_strcmp(argv[1], "3") == 0)
        result = mx_add_user_to_table(argv[2], argv[3], mx_atoi(argv[4]));
    else if (argc == 3 && mx_strcmp(argv[1], "4") == 0)
        result = mx_delete_user(argv[2]);
    else if (argc == 4 && mx_strcmp(argv[1], "5") == 0)
        result = mx_change_log(argv[2], argv[3]);
    else if (argc == 4 && mx_strcmp(argv[1], "6") == 0)
        result = mx_change_pass(argv[2], argv[3]);
    else if (argc == 4 && mx_strcmp(argv[1], "7") == 0) {
        t_list *list = mx_send_list_back(argv[2], mx_atoi(argv[3]));

        for (t_list *node = list; node; node = node->next) {
            printf("%s\t%s\t", ((t_table_list *)node->data)->name, ((t_table_list *)node->data)->path_img);
            printf("%s\t", ((t_table_list *)node->data)->last_mssg ? ((t_table_list *)node->data)->last_mssg : "NULL");
            printf("%s\n", ((t_table_list *)node->data)->last_mssg_time ? ((t_table_list *)node->data)->last_mssg_time : "NULL");
        }
    }
    else if (argc == 4 && mx_strcmp(argv[1], "8") == 0)
        result = mx_change_img(argv[2], argv[3]);
    else if (argc == 8 && mx_strcmp(argv[1], "9") == 0) {
        t_input data;
        data.name_from = mx_strdup(argv[2]);
        data.name_to = mx_strdup(argv[3]);
        data.message = mx_strdup(argv[4]);
        data.flag = mx_atoi(argv[5]);
        data.reply = mx_strdup(argv[6]);
        data.forward = mx_strdup(argv[7]);
        if (mx_atoi(argv[5]) == 1)
            data.file_name = mx_strdup(argv[4]);
        else
            data.file_name = mx_strdup("NULL");

        result = mx_recv_new_mess(&data);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "10") == 0) {
        t_list *list = mx_history_back(argv[2], argv[3], argv[4]);

        mx_print_list(list, argv[2], argv[3]);
    }
    else if (argc == 4 && mx_strcmp(argv[1], "11") == 0)
        result = mx_del_history(argv[2], argv[3]);
    else if (argc == 5 && mx_strcmp(argv[1], "12") == 0)
        result = mx_del_message(argv[2], argv[3], argv[4]);
    else if (argc == 6 && mx_strcmp(argv[1], "13") == 0)
        result = mx_edit(argv[2], argv[3], argv[4], argv[5]);
    else if (argc == 4 && mx_strcmp(argv[1], "14") == 0)
        mx_check_user_pass(argv[2], argv[3]) ? printf("ok :)\n") : printf("not ok T_T\n");
    else if (argc == 4 && mx_strcmp(argv[1], "15") == 0)
        printf("%s\n", mx_hash(argv[1], argv[2]));
    else if (argc == 5 && mx_strcmp(argv[1], "16") == 0) {
        t_list *list = mx_user_search(argv[2], argv[3], argv[4]);

        for (t_list *node = list; node; node = node->next) {
            printf("%s\t", ((t_table_list *)node->data)->name);
            printf("%s\n", ((t_table_list *)node->data)->path_img);
        }
    }
    else if (argc == 6 && mx_strcmp(argv[1], "17") == 0) {
        t_list *list = mx_mssg_search(argv[2], argv[3], argv[4], argv[5]);

        mx_print_list(list, argv[2], argv[3]);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "18") == 0)
        result += mx_set_type(argv[2], argv[3], mx_atoi(argv[4]));
    else if (argc == 4 && mx_strcmp(argv[1], "19") == 0)
        printf("%d\n", mx_get_type(argv[2], mx_atoi(argv[3])));
    else if (argc == 5 && mx_strcmp(argv[1], "20") == 0) {
        char *img_name = NULL;
        char *path = mx_get_img_path(argv[2], argv[3], mx_atoi(argv[4]), &img_name);

        printf("%s\t%s\n", path, img_name);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "21") == 0)
        result += mx_del_user_from_table(argv[2], argv[3], mx_atoi(argv[4]));
    // system("leaks -q uchat");
    return result;
}*/

// int main() {
//     int result = 0;

//     result += mx_add_new_user("Yarik", "Yarik", "Yarik.jpg");
//     result += mx_add_new_user("Ilya", "Ilya", "Ilya.jpg");
//     result += mx_add_new_user("Olya", "Olya", "Olya.jpg");
//     result += mx_add_new_user("PetFriend", "PetFriend", "PetFriend.jpg");

//     result += mx_copy("./Yarik.jpg", "./../database/Yarik/Yarik.jpg");
//     result += mx_copy("./Ilya.jpg", "./../database/Ilya/Ilya.jpg");
//     result += mx_copy("./Olya.jpg", "./../database/Olya/Olya.jpg");
//     result += mx_copy("./PetFriend.jpg", "./../database/PetFriend/PetFriend.jpg");
//     return result;
// }


