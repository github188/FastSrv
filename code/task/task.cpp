/*
//
//	Last Modify Date: 2015-11-05
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
		printf("formal  : task -address 192.168.1.65 -heartbeat 21000 -interval 30(second) -port 21010 -redis upload 6379 -redis sending 6380 -database coglink2/coglink2013@CLORCL -log path ../log/task.log \n");
		printf("example : task -a 192.168.1.65 -h 21000 -i 30 -p 21010 -r 6379 -s 6380 -d coglink2/coglink2013@CLORCL -l ../log/task.log \n");
		return 0;
	}

	common::Log* lo = common::Log::instance(cfg.getString('l').c_str());

	TaskHandle* th = new TaskHandle(cfg.getString('d'));
	if(th->db _EQ_ NULL)
	{
		LOG_DEBUG("initialize database error");
		return 0;
	}

	session::RedisQueue* rq_upload = new session::RedisQueue("127.0.0.1", cfg.getInt('r'), NULL, NULL);
	session::RedisQueue* rq_sending = new session::RedisQueue("127.0.0.1", cfg.getInt('s'), NULL, NULL);

	th->rc_upload = rq_upload->getRedisConn();
	th->rc_sending = rq_sending->getRedisConn();

	if(th->rc_upload == NULL || th->rc_sending == NULL)
	{
		LOG_DEBUG("connect redis error");
		return 0;
	}

	common::Thread* thread = new common::Thread;
	//event
	session::Session* se = new session::Session(session::SESSION_TYPE_LISTENER, NULL, cfg.getInt('p'), thread, th);
	se->start();
	// heartbeat slave
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(session::HB_SLAVE, cfg.getString('a').c_str(), cfg.getInt('h'), cfg.getInt('i'), cfg.getInt('p'), thread, hbm);
	hb->start();
	hbm->setLoad(0);
	thread->join();

	return 0;
}
