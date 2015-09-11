/*
//
//	Last Modify Date: 2015-09-11
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 处理能快速响应的事务
//
//
*/

#include "accepter.h"

int main(int argc, char* argv[])
{
	common::ConfigMap mapConfig;
	common::getConfigMap(argc, argv, "i:p:", mapConfig);

	if(mapConfig.find("i") == mapConfig.end() ||
		mapConfig.find("p") == mapConfig.end())
	{
		printf("\n formal  : accepter -interval 30(second) -port 2000 \n example : accepter -i 30 -p 2000 \n");
		return 0;
	}

	common::HeartBeat* hb = new common::HeartBeat;
	hb->interval = atoi(mapConfig.find("i")->second.c_str());
	hb->port = atoi(mapConfig.find("p")->second.c_str());

	// TODO : operation on the load must add lock
	hb->load = 0;

	common::Thread* thread = new common::Thread;
	if(thread->create(hb->slave, (void*)hb) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	sleep(6);

	// operation on the load must add lock
	hb->load = 1;

	thread->join();

	return 0;
}