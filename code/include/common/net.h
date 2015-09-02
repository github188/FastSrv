/*
//
//	Last Modify Date: 2015-09-02
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: public
//	Future:
//					I. 网络接口
//
//
*/

#ifndef _COMMON_NET_H_
#define _COMMON_NET_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include "event2/event.h"
#include "event2/util.h"
#include "event2/listener.h"
#include "event2/bufferevent.h"

using namespace std;

namespace common
{
	enum CONN_TYPE
	{
		CONN_TYPE_LISTENER = 0x01,
		CONN_TYPE_CONNECTER = 0x02
	};

	typedef void (*OnConnCb)(struct bufferevent *bev, void *conn);
	typedef void (*OnReadCb)(struct bufferevent *bev, void *conn);

	class Conn
	{
	public:
		unsigned int conn_type;
		char addr[64];
		struct sockaddr_in sAddrIn;
		struct event_base* pEvbase;
	public:
		OnConnCb OnConnCbAddr;
		OnReadCb OnReadCbAddr;
	public:
		void init(const unsigned int conn_type, const char* ip, const unsigned port);
		void setConnCb(OnConnCb inConnCbAddr);
		void setReadCb(OnReadCb inReadCbAddr);
		void run();
	public:
		int recvMsg(struct bufferevent* pEvbuf, void* data, size_t size);
		int sendMsg(struct bufferevent* pEvbuf, void* data, size_t size);
	private:
		static void OnConnListenerCb(struct evconnlistener *evListener, evutil_socket_t evSocket, struct sockaddr *pAddrIn, int socklen, void *arg);
		static void OnConnListenerErrCb(struct evconnlistener *evListener, void *arg);
		static void OnConnEventCb(struct bufferevent *bev, short what, void *ctx);
	};// class Conn
};// namespace common

#endif