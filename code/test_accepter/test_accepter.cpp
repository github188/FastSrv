/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. accepter 测试
//
//
*/

#include "test_accepter.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "c:p:");
	if(!cfg.exist('c') && !cfg.exist('p'))
	{
		printf("formal  : test_accepter -c(peer address) 192.168.1.65 -port 21010 \n");
		printf("example : test_accepter -c 192.168.1.65 -p 21010 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/test_accepter.log");
	common::Thread* thread = new common::Thread;

	// event
	AccepterHandle* ah = new AccepterHandle;
	session::Session* se = new session::Session(session::SESSION_TYPE_CONNECTER, cfg.getString('c').c_str(), cfg.getInt('p'), thread, ah);
	se->start();

	thread->join();

	return 0;
}
