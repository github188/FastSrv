/*
//
//	Last Modify Date: 2015-10-21
//	Author: zengpw
//	History:
//					2015-10-09 zengpw created
//	File Property: private
//	Future:
//					I. 消息分析和入库
//
//
*/

#include "upload.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "r:");

	if(!cfg.exist('r'))
	{
		printf("formal  : upload -redis 6379 \n");
		printf("example : upload -r 6379 \n");
		return 0;
	}

	common::Log* lo = common::Log::instance("../log/upload.log");
	common::Thread* thread = new common::Thread;

	// event
	UploadHandle* uh = new UploadHandle("coglink2/coglink2013@CLORCL");
	if(uh->db _EQ_ NULL)
	{
		LOG_DEBUG("initialize database error");
		return 0;
	}

	session::RedisQueue* rq = new session::RedisQueue("127.0.0.1", cfg.getInt('r'), thread, uh);
	rq->start();

	thread->join();

	return 0;
}
