////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//					2014-9-24 zengpw 重新设计
//	File Property : public
//	Description :
//					I. 提供线程池，全局唯一
//					II. 线程总数是固定的，但是线程本身是可复用的
//	Future :
//					I. 重新考虑锁的设计
//					II. 考虑在 loop() 中优雅的获取子线程自身
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_thread_pool.h"
#include "sys_func.h"

namespace PS_FW
{
	ThreadPool::ThreadPool(int size)
	{
		pthread_mutex_init(&m_lock,NULL);
		pthread_cond_init(&m_condLock,NULL);

		m_st = 1;
		m_vcThread.reserve(size);

		for (int i = 0;i < size;++i)
		{
			Thread* pThread = new Thread(loop,this);
			m_vcThread.push_back(pThread);

			//等待子线程创建完成
			//等待子线程获取自己在 vector 中的位置，暂时想不出更好的方法了；
			PS_FW::SYS_FUNC::sleep(1000);
		}

		printf("\n[PS_FW::ThreadPool] ThreadPool Create Success ! \n");
	}


	ThreadPool::~ThreadPool()
	{
// 		if (empty())
// 		{
// 			pthread_mutex_unlock(&m_lock);
// 			for (int i = 0;i < m_vcThread.size();++i)
// 			{
// 				pthread_cond_signal(&m_condLock);
// 			}
// 			pthread_mutex_destroy(&m_lock);
// 		}
	}


	void* ThreadPool::loop(void* pool)
	{
		//等待子线程 push 进主线程池
		PS_FW::SYS_FUNC::sleep(500);

		ThreadPool* pThreadPool = (ThreadPool*)pool;
		int i = pThreadPool->m_vcThread.size() - 1;
		Thread* pThread = (Thread*)pThreadPool->m_vcThread.at(i);
		printf("\n[PS_FW::ThreadPool] at(%d) is loop ! \n",i);

		while(1)
		{
			pthread_mutex_lock(&pThreadPool->m_lock);

			while(pThread->getEventStatus() != 0)
				pthread_cond_wait(&pThreadPool->m_condLock,&pThreadPool->m_lock);

			if(pThreadPool->m_st == 0)
			{
				pthread_mutex_unlock(&pThreadPool->m_lock);
				break;
			}

			pthread_mutex_unlock(&pThreadPool->m_lock);

			//启动内层回调
			pThread->callEvent();
		}

		pthread_exit(NULL);

		return NULL;
	}


	int ThreadPool::add(func_addr func,func_arg arg)
	{
		int i = 0;

		pthread_mutex_lock(&m_lock);

		for (i = 0;i < m_vcThread.size();++i)
		{
			if(m_vcThread.at(i)->getEventStatus() == -1)
			{
				m_vcThread.at(i)->attach(func,arg);
				break;
			}
		}

		pthread_mutex_unlock(&m_lock);

		printf("\n[PS_FW::ThreadPool] at(%d) is attach ! now do signal it \n",i);
		pthread_cond_signal(&m_condLock);

		return 0;
	}
}	//PS_FW

