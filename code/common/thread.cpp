/*
//
//	Last Modify Date: 2015-08-31
//	Author: zengpw
//	History:
//					2015-08-27 zengpw created
//	File Property: public
//	Future:
//					I. 线程
//
//
*/

#include "thread.h"

namespace common
{
	int Thread::create(void* (*start_rtn)(void*), void* arg)
	{
		SThread sThread;

		if(pthread_create(&sThread.pid, NULL, start_rtn, arg) == 0)
		{
			work = 1;
			sThread.exit = NULL;
			vecSThread.push_back(sThread);

			return 0;
		}
		else
		{
			return -1;
		}
	}


	void Thread::join()
	{
		for(int i = 0; i < vecSThread.size(); i++)
		{
			if(pthread_join(vecSThread[i].pid, &vecSThread[i].exit) == 0)
			{
				printf("\n thread %lld exit, exit code = %d\n", (long long)vecSThread[i].pid, (int*)vecSThread[i].exit);
			}
			else
			{
				printf("\n join thread error, pid = %lld\n", (long long)vecSThread[i].pid);
			}
		}
	}


	int Thread::stop()
	{
		work = 0;
	}
};// namespace common
