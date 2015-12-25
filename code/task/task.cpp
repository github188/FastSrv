/*
//
//	Last Modify Date: 2015-12-25
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
	common::Config cfg(argc, argv, "r:s:d:i:a:h:p:l:");

	if(!cfg.exist('r') || !cfg.exist('s') || !cfg.exist('d') || !cfg.exist('i') || !cfg.exist('a') || !cfg.exist('h') || !cfg.exist('p') || !cfg.exist('l'))
	{
		printf("formal  : task -address 220.248.44.218 -heartbeat 21000 -interval 30(second) -port 22001 -redis upload 6379 -redis sending 6380 -database coglink2/coglink2013@CLORCL -log path ../log/task.log \n");
		printf("example : task -a 220.248.44.218 -h 21000 -i 30 -p 22001 -r 6379 -s 6380 -d coglink2/coglink2013@CLORCL -l ../log/task.log \n");
		return 0;
	}

	common::Log::create(cfg.getString('l').c_str());

	TaskHandle* th = new TaskHandle(cfg.getString('d'));
	if(th->db _EQ_ NULL)
	{
		LOG_DEBUG("initialize database error");
		return 0;
	}

	session::RedisQueue* rq_upload = new session::RedisQueue("127.0.0.1", cfg.getInt('r'));
	session::RedisQueue* rq_sending = new session::RedisQueue("127.0.0.1", cfg.getInt('s'));

	th->rc_upload = rq_upload->open();
	th->rc_sending = rq_sending->open();

	if(th->rc_upload == NULL || th->rc_sending == NULL)
	{
		LOG_DEBUG("connect redis error");
		return 0;
	}

	common::Thread* thread = new common::Thread;
	//heartbeat slave
	session::HeartBeat::create(cfg.getString('a').c_str(), cfg.getInt('h'), cfg.getInt('i'), cfg.getInt('p'), thread);
	//event
	session::Session* se = new session::Session(session::SESSION_TYPE_LISTENER, NULL, cfg.getInt('p'), thread, th);
	se->start();

	return thread->join();
}
