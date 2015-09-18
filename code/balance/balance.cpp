/*
//
//	Last Modify Date: 2015-09-15
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
		printf("\n formal  : balance -heartbeat 21000 -port 21001 \n example : balance -h 21000 -p 21001 \n");
		return 0;
	}

	common::Thread* thread = new common::Thread;

	// event
	BalanceHandle* bh = new BalanceHandle;
	session::Session* se = new session::Session(thread, &cfg, bh);
	se->start();

	// heartbeat master
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::HeartBeat* hb = new session::HeartBeat(hbm);
	hb->port = atoi(cfg.get('h').c_str());
	if(thread->create(hb->master, (void*)hb) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	thread->join();

	return 0;
}
