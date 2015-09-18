/*
//
//	Last Modify Date: 2015-09-18
//	Author: zengpw
//	History:
//					2015-09-18 zengpw created
//	File Property: public
//	Future:
//					I. 负载均衡测试
//
//
*/

#include "test_balance.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "p:");
	if(!cfg.exist('p'))
	{
		printf("\n formal  : test_balance -port 21001 \n example : balance -p 21001 \n");
		return 0;
	}

	common::Thread* thread = new common::Thread;

	// event
	BalanceHandle* bh = new BalanceHandle;
	session::Session* se = new session::Session(thread, &cfg, bh);
	se->start();

	thread->join();

	return 0;
}
