////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月22日 zengpw 重新设计
//					2014年9月3日 zengpw 重新设计
//	File Property : private
//	Description : 
//				I. 线程
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "thread.h"

namespace PS_FW
{
	Thread::Thread(void* (*threadCallback)(void*),void* pSubject)
	{
		if(pthread_mutex_init(&m_mxLock,NULL) != 0)
		{
			delete this;
			printf("\n[PS_FW::Thread] thread_mutex_init fail!");
		}

		/* 此处由于使用 pthread 库，里面传给线程的地址，必须是函数地址 */
		if( pthread_create(&this->m_tid,NULL,threadCallback,pSubject) == 0 )
		{
			pthread_detach(this->m_tid);
			printf("\n[PS_FW::Thread] pthread_create ok! \n");
		}
	}

	Thread::~Thread()
	{
		pthread_mutex_destroy(&m_mxLock);
		exit;
	}
}	//PS_FW

