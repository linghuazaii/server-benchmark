#include "common.h"
#include "socket_wrapper.h"

const char *server_response_http = "HTTP/1.1 200 OK\r\n"
                                   "Cache-Control: private, max-age=0\r\n"
                                   "Content-Length: 30\r\n"
                                   "Content-Type: text/html; charset=utf-8\r\n"
                                   "Vary: Accept-Encoding\r\n"
                                   "Server: Microsoft-IIS/8.5\r\n"
                                   "P3P: CP=\"NON UNI COM NAV STA LOC CURa DEVa PSAa PSDa OUR IND\"\r\n"
                                   "X-MSEdge-Ref: Ref A: C89B635D4AC348D4A1058EB28F2B6D36 Ref B: ADD7C0A6AB58D6E7997686B337499181 Ref C: Tue Dec 13 00:48:26 2016 PST\r\n"
                                   "Date: Tue, 13 Dec 2016 08:48:25 GMT\r\n"
                                   "\r\n"
                                   "I returned something actually!";
/* will not generate any signal
 * @millisecond: millisecond to sleep
 * implement with select
 */
int msleep(int millisecond) {
    struct timeval timeout;
    timeout.tv_sec = millisecond / 1000;
    timeout.tv_usec = (millisecond % 1000) * 1000;
    
    int rc = select(0, NULL, NULL, NULL, &timeout);
    if (rc == -1) {
        SYSLOG("select() in msleep() (%s)", strerror(errno));
    }

    return rc;
}

/* fake as a real server */
void handle_request() {
    srandom(time(NULL));
    /* sleep for 30 - 50 milliseconds */
    int sleep_time = (random() % 20) + 30;
    msleep(sleep_time);
}

/* return a normal http response 
 * @fd: socket to send response
 */
int server_response(int fd) {
    return w_write(fd, server_response_http, strlen(server_response_http));
}

int reuse_address(int sockfd) {
    int on = 1;
    int rc = w_setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    
    return rc;
}
