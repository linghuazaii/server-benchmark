#include "socket_wrapper.h"

int w_socket(int domain, int type, int protocol) {
    int rc = socket(domain, type, protocol);
    if (rc == -1) {
        SYSLOG("socket() (%s)", strerror(errno));
    }

    return rc;
}

int w_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
    int rc;
    do {
        rc = connect(socket, address, address_len);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1){
            SYSLOG("connect() (%s)", strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_bind(int socket, const struct sockaddr *address, socklen_t address_len) {
    int rc = bind(socket, address, address_len);
    if (rc == -1)
        SYSLOG("bind() (%s)", strerror(errno));

    return rc;
}

int w_listen(int socket, int backlog) {
    int rc = listen(socket, backlog);
    if (rc == -1) 
        SYSLOG("listen() (%s)", strerror(errno));

    return rc;
}

int w_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int rc;
    do {
        rc = accept(sockfd, addr, addrlen);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1){
            SYSLOG("accept() (%s)", strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags) {
    int rc;
    do {
        rc = accept4(sockfd, addr, addrlen, flags);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1) {
            SYSLOG("accept4() (%s)", strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_read(int fildes, void *buf, size_t nbyte) {
    int rc;
    do {
        rc = read(fildes, buf, nbyte);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1) {
            SYSLOG("read(%d) (%s)", fildes, strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_write(int fildes, const void *buf, size_t nbyte) {
    int rc;
    do {
        rc = write(fildes, buf, nbyte);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1) {
            SYSLOG("write(%d) (%s)", fildes, strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_close(int fildes) {
    int rc;
    do {
        rc = close(fildes);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1) {
            SYSLOG("close(%d) (%s)", fildes, strerror(errno));
            break;
        } else
            break;
    } while (true);

    return rc;
}

int w_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    int rc = setsockopt(sockfd, level, optname, optval, optlen);
    if (rc == -1)
        SYSLOG("setsockopt() (%s)", strerror(errno));

    return rc;
}

int w_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int rc = 0;
    do {
        rc = select(nfds, readfds, writefds, exceptfds, timeout);
        if (rc == -1 && errno == EINTR)
            continue;
        else if (rc == -1) {
            SYSLOG("select() (%s)", strerror(errno));
            break;
        } else
            break;
    } while (true);
}
