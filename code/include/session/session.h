/*
//
//	Last Modify Date: 2015-10-12
//	Author: zengpw
//	History:
//					2015-09-15 zengpw created
//	File Property: public
//	Future:
//					I. 进一步封装 net层 和 protocol层
//
//
*/

#ifndef _SESSION_SESSION_H_
#define _SESSION_SESSION_H_

#include "common/thread.h"
#include "common/process.h"
#include "common/net.h"
#include "common/log.h"
#include "handle_basic.h"

using namespace std;

namespace session
{
	enum SESSION_TYPE
	{
		SESSION_TYPE_LISTENER = 0x01,
		SESSION_TYPE_CONNECTER = 0x02
	};

	class Session
	{
	public:
		unsigned int session_type;
		char addr[64];
		unsigned int port;
	public:
		common::Thread* th;
		HandleBasic* hb;
	public:
		explicit Session(const unsigned int session_type, const char* ip, unsigned int port, common::Thread* th, HandleBasic* hb);
	public:
		void start();
	public:
		static void* listenerCb(void* self);
		static void* connecterCb(void* self);
		static void OnConnCb(struct bufferevent *bev, void *conn);
		static void OnReadCb(struct bufferevent *bev, void *conn);
	};
};// namespace session

#endif