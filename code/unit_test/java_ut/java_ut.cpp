/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-11-05 zengpw created
//	File Property: private
//	Future:
//					I. 消息下发测试
//
//
*/

#include "java_ut.h"

int main(int argc, char* argv[])
{
	common::Config cfg(argc, argv, "h:p:l:");

	if(!cfg.exist('h') || !cfg.exist('p') || !cfg.exist('l'))
	{
		printf("formal  : java_ut -host 192.168.1.65 -port 7777 -log path ../log/java_ut.log \n");
		printf("example : java_ut -h 192.168.1.65 -p 7777 -l ../log/java_ut.log \n");
		return 0;
	}

	common::Log::create(cfg.getString('l').c_str());

	JavaCli jc;
	jc.setIp(cfg.getString('h'));
	jc.setPort(cfg.getString('p'));
	jc.run(argc, argv);

	return 0;
}