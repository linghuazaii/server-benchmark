#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>
#include "threadpool.h"
using namespace std;
/*
 * fork() a new process to handle request
 */

#define MAXCONN 1000
#define BENCH_SNDBUF 5 * 1024 * 1024
#define BENCH_RCVBUF 5 * 1024 * 1024

typedef struct thread_data_tag {
    char request_buffer[REQUEST_BUFSIZ];
    int conn;
} thread_data_t;

void thread_routine(void *thread_data) {
    thread_data_t *data = (thread_data_t *)thread_data;

    //CALC_TIME_MS_P("COST", 
    do {
        int n = w_read(data->conn, data->request_buffer, sizeof(data->request_buffer));
        if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            break;
    } while (true);
    //handle_request();
    server_response(data->conn);
    w_close(data->conn);
    //);

    delete data;
}

int main(int argc, char **argv) {
    int socket_server = w_socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int on = 1;
    //w_setsockopt(socket_server, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(int));
    int wait_seconds = 6; /* 6s */
    /* good for http, should be tunned */
    //w_setsockopt(socket_server, IPPROTO_TCP, TCP_DEFER_ACCEPT, &wait_seconds, sizeof(int));

	int sndbuf = BENCH_SNDBUF, rcvbuf = BENCH_RCVBUF;
	w_setsockopt(socket_server, SOL_SOCKET, SO_SNDBUF, &sndbuf, sizeof(int));
	w_setsockopt(socket_server, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(int));

    reuse_address(socket_server);
    w_bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    w_listen(socket_server, BACKLOG);

    int thread_num = atoi(argv[1]);
    threadpool_t *thread_pool = threadpool_create(thread_num, MAX_QUEUE, 0);
    int epollfd = w_epoll_create(0);
    struct epoll_event listen_event = {0}, event;
    listen_event.events = EPOLLIN;
    listen_event.data.fd = socket_server;
    w_epoll_ctl(epollfd, EPOLL_CTL_ADD, socket_server, &listen_event);

    struct epoll_event events[MAXCONN];
    for (;;) {
        int count = w_epoll_wait(epollfd, events, MAXCONN, -1);
        for (int i = 0; i < count; ++i) {
            if (events[i].events & EPOLLIN) {
                if (events[i].data.fd == socket_server) {
                    int conn = w_accept4(socket_server, 0, 0, SOCK_NONBLOCK);
                    //int conn = w_accept(socket_server, 0, 0);
                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = conn;
                    w_epoll_ctl(epollfd, EPOLL_CTL_ADD, conn, &event);
                } else {
                    thread_data_t *data = new thread_data_t;
                    data->conn = events[i].data.fd;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &events[i]);
                    threadpool_add(thread_pool, thread_routine, data, 0);
                }
            }
        }
    }

    threadpool_destroy(thread_pool, threadpool_graceful);
    
    return 0;
}
