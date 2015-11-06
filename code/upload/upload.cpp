/*
//
//	Last Modify Date: 2015-11-06
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
	common::Config cfg(argc, argv, "r:d:l:");

	if(!cfg.exist('r') || !cfg.exist('d') || !cfg.exist('l'))
	{
		printf("formal  : upload -redis 6379 -database coglink2/coglink2013@CLORCL -log path ../log/upload.log \n");
		printf("example : upload -r 6379 -d coglink2/coglink2013@CLORCL -l ../log/upload.log \n");
		return 0;
	}

	common::Log* lo = common::Log::instance(cfg.getString('l').c_str());

	if(!common::PyCall::Initialize())
	{
		LOG_DEBUG("Initialize python script fail, pls check py_http.py in current path!");
		return 0;
	}

	LOG_DEBUG("load python script success.");

	UploadHandle* uh = new UploadHandle(cfg.getString('d'));
	if(uh->db _EQ_ NULL)
	{
		LOG_DEBUG("initialize database error");
		return 0;
	}

	session::RedisQueue* rq = new session::RedisQueue("127.0.0.1", cfg.getInt('r'), uh);
	rq->run();

	common::PyCall::Finalize();

	return 0;
}
