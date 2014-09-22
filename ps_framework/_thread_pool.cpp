////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//	File Property : public
//	Description :
//					I. 提供线程池，全局唯一
//	Future :
//					I. 重新考虑锁的设计
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_thread_pool.h"

namespace PS_FW
{
	ThreadPool::ThreadPool(int size)
	{
		if (pthread_mutex_init(&m_mxLock,NULL) != 0)
			delete this;

		m_status = 1;
		m_count = 0;
		m_vcThread.reserve(size);

		for (int i = 0;i < size;++i)
		{
			Thread* pThread = new Thread(loop,this);
			m_count++;
			m_vcThread.push_back(pThread);
		}
	}


	ThreadPool::~ThreadPool()
	{
		destroy();
		pthread_mutex_destroy(&m_mxLock);
	}


	bool ThreadPool::isEmpty(void* pool)
	{
		ThreadPool* p = (ThreadPool*)pool;

		if(p->m_status != 0 || p->m_count > 0 || !m_vcThread.empty())
		{
			return false;
		}

		return true;
	}


	void* ThreadPool::loop(void* pool)
	{
		ThreadPool* p = (ThreadPool*)pool;
		int i = p->m_vcThread.size() - 1;

		while(1)
		{
			pthread_mutex_lock(&p->m_mxLock);

			while(!p->isEmpty(p))
			{
				pthread_cond_wait(&p->m_vcThread.at(i)->m_condLock,&p->m_mxLock);
			}

			if(p->m_status == 0)
			{
				pthread_mutex_unlock(&p->m_mxLock);
				break;
			}

			pthread_mutex_unlock(&p->m_mxLock);

			if(p->m_vcThread.at(i)->m_status == 1)
			{
				func_addr fun = p->m_vcThread.at(i)->m_func;
				func_arg arg = p->m_vcThread.at(i)->m_arg;
				fun(arg);
				p->m_vcThread.at(i)->m_status = 0;
			}
		}

		pthread_exit(NULL);

		return NULL;
	}


	int ThreadPool::add(func_addr func,func_arg arg)
	{
		int i = 0;

		pthread_mutex_lock(&m_mxLock);

		for (i = 0;i < m_vcThread.size();++i)
		{
			if(m_vcThread.at(i)->m_status == 0)
			{
				m_vcThread.at(i)->m_func = func;
				m_vcThread.at(i)->m_arg = arg;
				m_vcThread.at(i)->m_status = 1;

				printf("\n[PS_FW::ThreadPool] add() i is %d ! \n",i);
				break;
			}
		}

		pthread_mutex_unlock(&m_mxLock);

		printf("\n[PS_FW::ThreadPool] at(i) i is %d ! \n",i);
		pthread_cond_signal(&m_vcThread.at(i)->m_condLock);

		return 0;
	}


	void ThreadPool::destroy()
	{
		pthread_mutex_lock(&m_mxLock);

		m_status = 0;

		pthread_mutex_unlock(&m_mxLock);

		for (int i = 0;i < m_vcThread.size();++i)
		{
			pthread_cond_signal(&m_vcThread.at(i)->m_condLock);
		}
	}
}	//PS_FW
