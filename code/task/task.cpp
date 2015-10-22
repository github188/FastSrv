/*
//
//	Last Modify Date: 2015-10-21
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息预处理
//
//
*/

#include "task.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "r:i:a:h:p:");

	if(!cfg.exist('r') || !cfg.exist('i') || !cfg.exist('a') || !cfg.exist('h') || !cfg.exist('p'))
	{
		printf("formal  : task -address 192.168.1.65 -heartbeat 21000 -interval 30(second) -port 21010 -redis 6379 \n");
		printf("example : task -a 192.168.1.65 -h 21000 -i 30 -p 21010 -r 6379 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/task.log");

	session::RedisQueue* rq = new session::RedisQueue("127.0.0.1", cfg.getInt('r'), NULL, NULL);

	common::Thread* thread = new common::Thread;

	// event
	TaskHandle* th = new TaskHandle;
	th->rc = rq->getRedisConn();

	if(th->rc == NULL)
	{
		LOG_DEBUG("connect redis error");
		return 0;
	}

	session::Session* se = new session::Session(session::SESSION_TYPE_LISTENER, NULL, cfg.getInt('p'), thread, th);
	se->start();

	// heartbeat slave
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(session::HB_SLAVE, cfg.getString('a').c_str(), cfg.getInt('h'), cfg.getInt('i'), cfg.getInt('p'), thread, hbm);
	hb->start();

	thread->join();

	return 0;
}
