////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月22日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description : 
//				I. 线程
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "thread.h"

namespace PS_FW
{
	//为跨平台库 pthread 写的 C 风格回调函数
	void* threadCallback(void* arg)
	{
		Thread* pThread = (Thread*)arg;
		pThread->OnThreadRun();

		return NULL;
	}

	Thread::Thread()
	{
		if(pthread_mutex_init(&this->m_mxLock,NULL) != 0)
		{
			delete this;
			printf("\n[ps_fw_framework] thread_mutex_init fail!");
		}

		/* 此处由于使用 pthread 库，里面传给线程的地址，必须是函数地址 */
		if( pthread_create(&this->m_tid,NULL,threadCallback,(void*)this) == 0 )
		{
			pthread_detach(this->m_tid);
		}
	}
}	//PS_FW

