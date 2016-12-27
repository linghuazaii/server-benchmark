#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
#include "threadpool.h"
#include <iostream>
#include <queue>
using namespace std;
/*
 * fork() a new process to handle request
 */

#define MAXCONN 1000

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

    int thread_num = atoi(argv[1]);
    threadpool_t *thread_pool = threadpool_create(thread_num, MAX_QUEUE, 0);
    struct pollfd fds[MAXCONN];
    queue<pollfd *> free_fds;
    for (int i = 1; i < MAXCONN; ++i) {
        fds[i].fd = -1;
        free_fds.push(&fds[i]);
    }
    fds[0].fd = socket_server;
    fds[0].events = POLLIN | POLLPRI;
    for (;;) {
        int count = w_poll(fds, MAXCONN, -1);
        for (int i = 0; i < MAXCONN; ++i) {
            if (fds[i].revents == POLLIN) {
                if (fds[i].fd == socket_server) {
                    int conn = w_accept(socket_server, 0, 0);
                    pollfd *one = free_fds.front();
                    free_fds.pop();
                    one->fd = conn;
                    one->events = POLLIN | POLLPRI;
                } else {
                    thread_data_t *data = new thread_data_t;
                    data->conn = fds[i].fd;
                    fds[i].fd = -1;
                    free_fds.push(&fds[i]);
                    threadpool_add(thread_pool, thread_routine, data, 0);
                }
            }
        }
    }

    threadpool_destroy(thread_pool, threadpool_graceful);
    
    return 0;
}
