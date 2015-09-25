/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: private
//	Future:
//					I. 负载均衡
//
//
*/

#include "balance.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "h:p:");
	if(!cfg.exist('h') || !cfg.exist('p'))
	{
		printf("formal  : balance -heartbeat 21000 -port 21001 \n");
		printf("example : balance -h 21000 -p 21001 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/balance.log");

	common::Thread* thread = new common::Thread;

	// event
	BalanceHandle* bh = new BalanceHandle;
	session::Session* se = new session::Session(session::SESSION_TYPE_LISTENER, NULL, cfg.getInt('p'), thread, bh);
	se->start();

	// heartbeat master
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(session::HB_MASTER, NULL, cfg.getInt('h'), 0, thread, hbm);
	hb->start();

	thread->join();

	return 0;
}
