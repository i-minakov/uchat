#include "../../inc/header.h"

int mx_daemon_state(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid < 0)
        perror("ush: fork");
    else if (pid == 0) {
        if(setsid() < 0)
            exit(EXIT_FAILURE);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        mx_server(argc, argv);
    }
    else
        exit(EXIT_SUCCESS);
    return 0;
}
