/*
//
//	Last Modify Date: 2015-08-28
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
		CONN_TYPE_CONNECTER = 0x02,
		CONN_TYPE_ADAPTER = 0x04
	};

	enum CONN_EVENT
	{
		CONN_EVENT_READ = 0x01,
		CONN_EVENT_WRITE = 0x02
	};

	typedef void (*dataHandleCb)(void* conn, struct bufferevent* pEvbuf, int conn_event);

	class Conn
	{
	public:
		unsigned int conn_type;
		unsigned int port;
		struct event_base* pEvbase;
		struct evconnlistener* pEvConn;
		// struct bufferevent* pEvBuf;
		// evutil_socket_t evSocketId;
		dataHandleCb OnDataHandleCb;
	public:
		int init(unsigned int in_conn_type);
		int setPort(unsigned int in_port);
		void setDataHandleCb(dataHandleCb inDataHandleCb);
		int run();
		int recvMsg(struct bufferevent* pEvbuf, void* data, size_t size);
		int sendMsg(struct bufferevent* pEvbuf, void* data, size_t size);
	private:
		static void OnConnListenerCb(struct evconnlistener *evListener, evutil_socket_t evSocket, struct sockaddr *pAddrIn, int socklen, void *arg);
		static void OnConnListenerErrCb(struct evconnlistener *evListener, void *arg);
		static void OnConnBuffereventErrCb(struct bufferevent *bev, short what, void *ctx);
		static void OnReadCb(struct bufferevent *bev, void *ctx);
		static void OnWriteCb(struct bufferevent *bev, void *ctx);
	};// class Conn
};// namespace common

#endif