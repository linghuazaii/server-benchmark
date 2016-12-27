#include "socket_wrapper.h"
#include "common.h"
#include <signal.h>
#include <pthread.h>
#include <sys/epoll.h>
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

    reuse_address(socket_server);
    w_bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    w_listen(socket_server, BACKLOG);

    int thread_num = atoi(argv[1]);
    threadpool_t *thread_pool = threadpool_create(thread_num, MAX_QUEUE, 0);
    int epollfd = w_epoll_create(0);
    for (;;) {
    }

    threadpool_destroy(thread_pool, threadpool_graceful);
    
    return 0;
}
