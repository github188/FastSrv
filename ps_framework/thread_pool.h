#ifndef __PS_FW_THREAD_POOL__
#define __PS_FW_THREAD_POOL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月22日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :
//				I. 线程池
//
////////////////////////////////////////////////////////////////////////////////////////

#include "thread.h"

namespace PS_FW
{
	typedef std::list<Thread*> ThreadList;

	class ThreadPool
	{
	public:
		ThreadPool(void* (*threadCallback)(void*),void* pSubject,int size);
		virtual ~ThreadPool();
	public:
		int append(Thread* pThread);
	protected:
		ThreadList* m_pool;
	};
}	//PS_FW

#endif //__PS_FW_THREAD_POOL__

