#include "socket_wrapper.h"
#include "common.h"
/*
 * |---------|       |--------|
 * | Request | ====> | Server |    ***********************
 * |---------|       |--------|    * Single Thread Modle *
 *                       ||        ***********************
 *                    |------|
 *                    | Read |                 
 *                    |------|      
 *                       ||                           
 *                   |--------|                       
 *                   | Handle |                                   
 *                   |--------|                                   
 *                       ||                               
 *                   |-------|
 *                   | Write |
 *                   |-------|
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
    char request_buffer[REQUEST_BUFSIZ];
    for (;;) {
        int conn = w_accept(socket_server, 0, 0);
        w_read(conn, request_buffer, REQUEST_BUFSIZ);
        handle_request();
        server_response(conn);
        w_close(conn);
    }

    return 0;
}
