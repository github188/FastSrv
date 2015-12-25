/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-10-28 zengpw created
//	File Property: private
//	Future:
//					I. 消息下发
//
//
*/

#include "sending.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "r:p:l:");

	if(!cfg.exist('r') || !cfg.exist('p') || !cfg.exist('l'))
	{
		printf("formal  : sending -redis 6380 -port 7777 -log path ../log/sending.log \n");
		printf("example : sending -r 6380 -p 7777 -l ../log/sending.log \n");
		return 0;
	}

	common::Log::create(cfg.getString('l').c_str());

	session::RedisQueue* rq = new session::RedisQueue("127.0.0.1", cfg.getInt('r'));
	common::Redis* rc = rq->open();
	if(rc == NULL)
	{
		LOG_DEBUG("connect redis error");
		return 0;
	}

	SendingSrv ss;
	ss.setPort(cfg.getString('p'));
	ss.setRedis(rc);

	return ss.main(argc, argv);
}