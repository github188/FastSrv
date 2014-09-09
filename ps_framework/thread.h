#ifndef __PS_FW_THREAD__
#define __PS_FW_THREAD__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月5日 zengpw 重新设计
//					2014年9月7日 zengpw 重新设计
//					2014年9月9日 zengpw 增加条件等待
//	File Property : private
//	Description :
//				I. 线程基类，提供启动线程的方法
//				Ⅱ. 它的构造、启动线程等一系列方法都是 protected 的，因此你必须要继承它才能使用它
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"

namespace PS_FW
{
	class Thread
	{
	public:
		Thread()
		{
			if(pthread_mutex_init(&m_mxLock,NULL) != 0)
			{
				delete this;
				printf("\n[PS_FW::Thread] thread_mutex_init fail!");
			}
		}


		virtual ~Thread()
		{
			pthread_mutex_destroy(&m_mxLock);
		}


		void join()
		{
			while (1)
			{
				//等待操作，目前只是做死循环
			}
		}
	protected:
		void run(void*(*pObjectCallBackFunc)(void*),void* pObject)
		{
			printf("\n[PS_FW::Thread] thread create start ! \n");
			if( pthread_create(&this->m_tid,NULL,pObjectCallBackFunc,pObject) == 0 )
			{
				pthread_detach(this->m_tid);
				printf("\n[PS_FW::Thread] thread create success ! \n");
			}
		}
	protected:
		pthread_t m_tid;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_THREAD__
