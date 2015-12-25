/*
//
//	Last Modify Date: 2015-12-25
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

	int Thread::join()
	{
		for(unsigned int i = 0; i < vecSThread.size(); i++)
		{
			if(pthread_join(vecSThread[i].pid, &vecSThread[i].exit) == 0)
			{
				LOG_DEBUG("thread exit, pid = " << vecSThread[i].pid << ", exit code = " << (int*)vecSThread[i].exit);
				//TODO: 如果是 session 线程退出，则需要发送 thread_cancel() 到 heartbeat 线程；最终触发整个进程退出
			}
			else
			{
				LOG_DEBUG("join thread error, pid = " << (long long)vecSThread[i].pid);
			}
		}

		return 0;
	}

	int Thread::stop()
	{
		work = 0;
		return 0;
	}
};// namespace common
