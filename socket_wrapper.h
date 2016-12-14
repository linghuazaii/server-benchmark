#ifndef _SOCKET_WRAPPER_H
#define _SOCKET_WRAPPER_H
#include "definition.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*
 * File: socket_wrapper.h
 * Description: system socket call wrappers
 * Author: Charles. 2016-12-14
 * Mailto: charlesliu.cn.bj@gmail.com
 */

int w_socket(int domain, int type, int protocol);
int w_connect(int socket, const struct sockaddr *address, socklen_t address_len);
int w_bind(int socket, const struct sockaddr *address, socklen_t address_len);
int w_listen(int socket, int backlog);
int w_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int w_accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);
int w_read(int fildes, void *buf, size_t nbyte);
int w_write(int fildes, const void *buf, size_t nbyte);
int w_close(int fildes);
int w_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

#endif
