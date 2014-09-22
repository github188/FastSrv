////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//	File Property : public
//	Description :
//					I. 提供单独启动线程的方法
//					II. 提供独立的元素供线程池使用
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_thread.h"

namespace PS_FW
{
	Thread::Thread()
	{
		initLock();
	}


	Thread::Thread(func_addr func,func_arg arg)
	{
		initLock();

		printf("\n[PS_FW::Thread] pthread_create start ! \n");
		if (pthread_create(&m_tid,NULL,func,arg) == 0)
		{
			printf("\n[PS_FW::Thread] pthread_create success ! \n");
		}
		else
		{
			printf("\n[PS_FW::Thread] pthread_create fail ! \n");
		}
	}


	Thread::~Thread()
	{
		destroyLock();
	}


	void Thread::join()
	{
		if(pthread_join(m_tid,NULL) == 0)
		{
			delete this;
		}
	}

	int Thread::initLock()
	{
		if (pthread_mutex_init(&m_mxLock,NULL) != 0)
			return -1;

		if(pthread_cond_init(&m_condLock,NULL) != 0)
			return -1;

		m_status = 0;
	}


	void Thread::destroyLock()
	{
		printf("\n[DRAGON::Thread] Thread signal destroy ! \n");

		if(pthread_cond_destroy(&m_condLock) != 0)
		{
			printf("\n[DRAGON::Thread] pthread_cond_destroy fail ! \n");
		}

		if(pthread_mutex_destroy(&m_mxLock) != 0)
		{
			printf("\n[DRAGON::Thread] pthread_mutex_destroy fail ! \n");
		}
	}
}	//PS_FW

