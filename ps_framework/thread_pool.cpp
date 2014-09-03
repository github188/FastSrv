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
//
////////////////////////////////////////////////////////////////////////////////////////

#include "thread_pool.h"

namespace PS_FW
{
	ThreadPool::ThreadPool(void* (*threadCallback)(void*),void* pSubject,int size)
	{
		m_pool = new ThreadList;
		m_pool->clear();
		for (int i = 0; i < size; ++i)
		{
			Thread* pThread = new Thread(threadCallback,pSubject);
			append(pThread);
		}
	}

	ThreadPool::~ThreadPool()
	{
		if(m_pool != NULL)
		{
			ThreadList::iterator pos;
			for (pos = m_pool->begin();pos != m_pool->end();++pos)
			{
				delete (*pos);
			}

			delete m_pool;
		}
	}

	int ThreadPool::append(Thread* pThread)
	{
		m_pool->push_back(pThread);

		return 0;
	}
}	//PS_FW


