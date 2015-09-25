/*
//
//	Last Modify Date: 2015-09-25
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
	common::Config cfg(argc, argv, "c:p:");
	if(!cfg.exist('c') && !cfg.exist('p'))
	{
		printf("formal  : test_balance -c(peer address) 192.168.1.65 -port 21001 \n");
		printf("example : test_balance -c 192.168.1.65 -p 21001 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/test_balance.log");
	common::Thread* thread = new common::Thread;

	// event
	BalanceHandle* bh = new BalanceHandle;
	session::Session* se = new session::Session(session::SESSION_TYPE_CONNECTER, cfg.getString('c').c_str(), cfg.getInt('p'), thread, bh);
	se->start();

	thread->join();

	return 0;
}
