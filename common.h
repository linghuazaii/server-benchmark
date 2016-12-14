#ifndef _SB_COMMON_H
#define _SB_COMMON_H
#include "definition.h"
/*
 * File: common.h
 * Description: common functions for all kind of servers
 * Author: Charles. 2016-12-14
 * Mailto: charlesliu.cn.bj@gmail.com
 */

extern const char *server_response_http;

int msleep(int milliseconda);
void handle_request();
int server_response(int fd);
int reuse_address(int sockfd);

#endif
