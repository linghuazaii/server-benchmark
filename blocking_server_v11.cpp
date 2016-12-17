#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
/*
 * fork() a new process to handle request
 */

extern int socket_server;

void *thread_routine(void *thread_conn) {
    char request_buffer[REQUEST_BUFSIZ];
    for (;;) {
        int conn = accept(socket_server, NULL, NULL);
        w_read(conn, request_buffer, REQUEST_BUFSIZ);
        handle_request();
        server_response(conn);
        w_close(conn);
    }

    return NULL;
}

int socket_server = 0;

int main(int argc, char **argv) {
    socket_server = w_socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    reuse_address(socket_server);
    w_bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    w_listen(socket_server, BACKLOG);

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < 2; ++i) {
        pthread_t thread_id;
        pthread_create(&thread_id, &thread_attr, thread_routine, NULL);
    }

    while (true) {
        sleep(86400);
    }

    pthread_attr_destroy(&thread_attr);

    return 0;
}
