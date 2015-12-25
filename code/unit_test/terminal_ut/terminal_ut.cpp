/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#include "terminal_ut.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "c:p:l:");
	if(!cfg.exist('c') || !cfg.exist('p') || !cfg.exist('l'))
	{
		printf("formal  : terminal_ut -c(peer address) 192.168.1.65 -port 22000 -log path ../log/terminal_ut.log \n");
		printf("example (conn balance) : terminal_ut -c 192.168.1.65 -p 22000 -l ../log/terminal_ut.log \n");
		printf("example (conn task)    : terminal_ut -c 192.168.1.65 -p 22001 -l ../log/terminal_ut.log \n");
		return 0;
	}

	common::Log::create(cfg.getString('l').c_str());

	string ip = cfg.getString('c');
	int port = cfg.getInt('p');

	//是否向分配器获取服务器地址
	#if 1
		LOG_DEBUG("get server ip begin ...");

		TerminalUtLogin* tul = new TerminalUtLogin;
		session::Session* se_srv = new session::Session(session::SESSION_TYPE_CONNECTER, ip.c_str(), port, NULL, tul);
		se_srv->startNoThread();
		ip = tul->ip;
		port = tul->port;

		LOG_DEBUG("new server ip = " << ip << ", port = " << port);
	#endif

	common::Thread* thread = new common::Thread;
	// event
	TerminalUtHandle* tu = new TerminalUtHandle;
	session::Session* se = new session::Session(session::SESSION_TYPE_CONNECTER, ip.c_str(), port, thread, tu);
	se->start();

	return thread->join();
}
