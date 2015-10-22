/*
//
//	Last Modify Date: 2015-10-14
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#include "task_ut.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "c:p:");
	if(!cfg.exist('c') && !cfg.exist('p'))
	{
		printf("formal  : task_ut -c(peer address) 192.168.1.65 -port 21010 \n");
		printf("example : task_ut -c 192.168.1.65 -p 21010 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/task_ut.log");
	common::Thread* thread = new common::Thread;

	// event
	TaskUtHandle* tuh = new TaskUtHandle;
	session::Session* se = new session::Session(session::SESSION_TYPE_CONNECTER, cfg.getString('c').c_str(), cfg.getInt('p'), thread, tuh);
	se->start();

	thread->join();

	return 0;
}
