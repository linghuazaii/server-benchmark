#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
/*
 * fork() a new process to handle request
 */

void *thread_routine(void *thread_conn) {
    int *conn = (int *)thread_conn;
    char request_buffer[REQUEST_BUFSIZ];
    w_read(*conn, request_buffer, REQUEST_BUFSIZ);
    handle_request();
    server_response(*conn);
    w_close(*conn);
    delete conn;

    return NULL;
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

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    for (;;) {
        int conn = w_accept(socket_server, 0, 0);
        pthread_t thread_id;
        int *thread_conn = new int();
        *thread_conn = conn;
        pthread_create(&thread_id, &thread_attr, thread_routine, thread_conn);
    }

    pthread_attr_destroy(&thread_attr);

    return 0;
}
