/*
//
//	Last Modify Date: 2015-10-21
//	Author: zengpw
//	History:
//					2015-10-10 zengpw created
//	File Property: public
//	Future:
//					I. 封装从 redis 队列存取数据事件
//
//
*/

#ifndef _REDIS_QUEUE_H_
#define _REDIS_QUEUE_H_

#include "common/thread.h"
#include "common/process.h"
#include "common/net.h"
#include "common/redis.h"
#include "common/db.h"
#include "common/log.h"
#include "handle_basic.h"

using namespace std;

namespace session
{
	class RedisQueue
	{
	public:
		char queue[10240];
		int len;
	public:
		//此处的成员变量 rc 仅仅作用于进程，只能被单线程使用，后续是否保留有待思考
		string ip;
		unsigned int port;
		common::Redis* rc;
	public:
		common::Thread* th;
		HandleBasic* hb;
	public:
		explicit RedisQueue(const string ip, const unsigned int port, common::Thread* th, HandleBasic* hb);
	public:
		common::Redis* getRedisConn();
	public:
		void start();
		static void* queueCb(void* self);
	};
};// namespace session

#endif