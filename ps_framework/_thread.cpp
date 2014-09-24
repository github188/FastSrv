////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//					2014-9-24 zengpw 优化说明和设计
//	File Property : public
//	Description :
//					I. 提供单独启动线程的方法
//					II. 部分设计的元素是为线程池使用的
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_thread.h"

namespace PS_FW
{
	Thread::Thread(func_addr func,func_arg arg)
	{
		pthread_mutex_init(&m_mxLock,NULL);

		if (pthread_create(&m_tid,NULL,func,arg) == 0)
		{
			printf("\n[PS_FW::Thread] pthread_create success ! \n");
			printf("\n[PS_FW::Thread:%d] pthread_create , m_tid is %d ! \n",pthread_self().x,m_tid.x);
		}
		else
		{
			printf("\n[PS_FW::Thread] pthread_create fail ! \n");
		}

		setStatus(1);
		setEventStatus(-1);
	}


	Thread::~Thread()
	{
		if(pthread_mutex_destroy(&m_mxLock) != 0)
		{
			printf("\n[PS_FW::Thread:%d] pthread_mutex_destroy fail , m_tid is %d ! \n",pthread_self().x,m_tid.x);
		}
	}


	void Thread::attach(func_addr func,func_arg arg)
	{
		pthread_mutex_lock(&m_mxLock);
		m_func = func;
		m_arg = arg;
		pthread_mutex_unlock(&m_mxLock);

		setEventStatus(0);
	}


	void Thread::detach()
	{
		pthread_mutex_lock(&m_mxLock);
		m_func = NULL;
		m_arg = NULL;
		pthread_mutex_unlock(&m_mxLock);

		setEventStatus(-1);
	}


	void Thread::callEvent()
	{
		if (getEventStatus() == 0)
		{
			setEventStatus(1);
			m_func(m_arg);
			detach();
		}
	}


	void Thread::join()
	{
		if(pthread_join(m_tid,NULL) == 0)
		{
			printf("\n[PS_FW::Thread:%d] pthread_join m_tid is %d ! \n",pthread_self().x,m_tid.x);
		}
	}


	int Thread::getStatus()
	{
		return m_status;
	}


	void Thread::setStatus(int st)
	{
		pthread_mutex_lock(&m_mxLock);
		m_status = st;
		pthread_mutex_unlock(&m_mxLock);
	}


	int Thread::getEventStatus()
	{
		return m_event;
	}


	void Thread::setEventStatus(int st)
	{
		pthread_mutex_lock(&m_mxLock);
		m_event = st;
		pthread_mutex_unlock(&m_mxLock);
	}
}	//PS_FW

