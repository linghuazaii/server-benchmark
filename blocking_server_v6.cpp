#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
/*
 * fork() a new process to handle request
 */

void start_server(int listenfd) {
    char request_buffer[REQUEST_BUFSIZ];
    for (;;) {
        int conn = w_accept(listenfd, 0, 0);
        w_read(conn, request_buffer, REQUEST_BUFSIZ);
        handle_request();
        server_response(conn);
        w_close(conn);
    }
}

int main(int argc, char **argv) {
    int socket_server = w_socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    reuse_address(socket_server);
    w_bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    w_listen(socket_server, BACKLOG);

    struct sigaction sigchld_action;
    sigchld_action.sa_handler = SIG_DFL;
    sigchld_action.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sigchld_action, NULL);

    /* fork 15 children */
    for (int i = 0; i < 1; ++i) {
        int child = fork();
        if (child == 0) {
            start_server(socket_server);
        } else
            continue;
    }

    start_server(socket_server);

    return 0;
}
