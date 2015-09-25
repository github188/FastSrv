/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息预处理
//
//
*/

#include "accepter.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "r:i:a:h:p:");

	if(!cfg.exist('r') || !cfg.exist('i') || !cfg.exist('a') || !cfg.exist('h') || !cfg.exist('p'))
	{
		printf("formal  : accepter -redis 6379 -interval 30(second) -address 192.168.1.65 -heartbeat 21000 -port 21010 \n");
		printf("example : accepter -r 6379 -i 30 -a 192.168.1.65 -h 21000 -p 21010 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/accepter.log");

	common::Thread* thread = new common::Thread;

	// event
	AccepterHandle* ah = new AccepterHandle;

	if(!ah->redis_init("127.0.0.1", cfg.getInt('r')))
	{
		LOG_DEBUG("redis_init error");
		return 0;
	}

	session::Session* se = new session::Session(session::SESSION_TYPE_LISTENER, NULL, cfg.getInt('p'), thread, ah);
	se->start();

	// heartbeat slave
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(session::HB_SLAVE, cfg.getString('a').c_str(), cfg.getInt('h'), cfg.getInt('i'), thread, hbm);
	hb->start();

	thread->join();

	return 0;
}
