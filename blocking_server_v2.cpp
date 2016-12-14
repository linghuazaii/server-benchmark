#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
/*
 * fork() a new process to handle request
 */

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

    for (;;) {
        int conn = w_accept(socket_server, 0, 0);
        pid_t child = fork();
        if (child == 0) {
            char request_buffer[REQUEST_BUFSIZ];
            w_read(conn, request_buffer, REQUEST_BUFSIZ);
            handle_request();
            server_response(conn);
            w_close(conn);
            exit(EXIT_SUCCESS);
        } else {
            w_close(conn); /* decrease reference count */
        }
    }

    return 0;
}
