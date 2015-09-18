/*
//
//	Last Modify Date: 2015-09-16
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
#include "session_handle.h"

using namespace std;

namespace session
{
	class Session
	{
	public:
		common::Thread* th;
		common::Config* cfg;
		SessionHandle* sh;
	public:
		explicit Session(common::Thread* th, common::Config* cfg, SessionHandle* sh);
	public:
		void start();
	public:
		static void* listenerCb(void* arg);
		static void OnReadCb(struct bufferevent *bev, void *conn);
	};
};// namespace session

#endif