/*
//
//	Last Modify Date: 2015-09-02
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

int main()
{
	common::Thread* thread = new common::Thread;
	common::HeartBeat* heartBeat = new common::HeartBeat;

	if(thread->create(heartBeat->slave, NULL) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	thread->join();

	return 0;
}