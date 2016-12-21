#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
#include "threadpool.h"
/*
 * fork() a new process to handle request
 */

typedef struct thread_data_tag {
    char request_buffer[REQUEST_BUFSIZ];
    int conn;
} thread_data_t;

void thread_routine(void *thread_data) {
    thread_data_t *data = (thread_data_t *)thread_data;

    //CALC_TIME_MS_P("COST", 
    w_read(data->conn, data->request_buffer, sizeof(data->request_buffer));
    //handle_request();
    server_response(data->conn);
    w_close(data->conn);
    //shutdown(data->conn, SHUT_RDWR);
    //);

    delete data;
}

void dump_fd_info(fd_set &readfds) {
    SYSLOG("FD INFO >");
    for (int i = 0; i < 1024; ++i)
        if (FD_ISSET(i, &readfds))
            SYSLOG("> %d", i);
    SYSLOG("");
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

    int max_fd = socket_server;
    int thread_num = atoi(argv[1]);
    threadpool_t *thread_pool = threadpool_create(thread_num, MAX_QUEUE, 0);
    fd_set readfds, activefds;
    FD_ZERO(&activefds);
    FD_SET(socket_server, &activefds);
    for (;;) {
        //dump_fd_info(activefds);
        readfds = activefds;
        int rc = w_select(max_fd + 1, &readfds, NULL, NULL, NULL);
        //CALC_TIME_MS_P("Main",
        //dump_fd_info(activefds);

        if (rc > 0) {
            int count = 0;
            for (int i = 3; i < max_fd + 1; ++i) {
                if (FD_ISSET(i, &readfds)) {
                    if (i == socket_server) {
                        int conn = w_accept(socket_server, NULL, NULL);
                        max_fd = MAX(conn, max_fd);
                        //SYSLOG("conn: %d maxfd: %d", conn, max_fd);
                        FD_SET(conn, &activefds);
                    } else {
                        thread_data_t *data = new thread_data_t;
                        data->conn = i;
                        FD_CLR(i, &activefds);
                        threadpool_add(thread_pool, thread_routine, data, 0);
                    }
                    ++count;
                    if (count == rc)
                        break;
                }
            }
        } else
            continue;
        //);
    }

    threadpool_destroy(thread_pool, threadpool_graceful);
    
    return 0;
}
