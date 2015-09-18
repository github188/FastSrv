/*
//
//	Last Modify Date: 2015-09-16
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
		printf("\n formal  : accepter -redis 6379 -interval 30(second) -address 192.168.1.65 -heartbeat 21000 -port 21010 \n");
		printf("\n example : accepter -r 6379 -i 30 -a 192.168.1.65 -h 21000 -p 21010 \n");
		return 0;
	}

	common::Thread* thread = new common::Thread;

	// event
	AccepterHandle* ah = new AccepterHandle;
	if(!ah->redis_init("127.0.0.1", atoi(cfg.get('r').c_str())))
	{
		printf("\n redis_init error \n");
		return 0;
	}

	session::Session* se = new session::Session(thread, &cfg, ah);
	se->start();

	// heartbeat slave
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(hbm);
	hb->interval = atoi(cfg.get('i').c_str());
	hb->addr = cfg.get('a');
	hb->port = atoi(cfg.get('h').c_str());
	if(thread->create(hb->slave, (void*)hb) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	thread->join();

	return 0;
}
