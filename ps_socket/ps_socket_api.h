#ifndef __PS_SOCKET_API_H__
#define __PS_SOCKET_API_H__

/* c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
/* linux */
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
/* socket */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
/* thread pool */
#include "ps_thread_api.h"

int socket_send_normal(int socketfd,const char* buf,size_t nbytes);
int socket_recv_normal(int socketfd,char* buf,size_t nbytes);
void wait_use_select(int socketfd,int(*event)(int));
void server_open(int(*event)(int));
int socket_create(const char* host,const unsigned short port,struct sockaddr_in& addr,int& socketfd);
int socket_open(const char* host,const unsigned short port,int& socketfd);
int socket_accept(const int sSocketfd,int& cSocketfd);
int socket_connect(const char* host,const unsigned short port,int& socketfd,int retry,const int sleep);
int socket_close(int& socketfd);

// __PS_SOCKET_API_H__
#endif
