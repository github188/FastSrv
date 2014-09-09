////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月9日 zengpw 重新设计
//	File Property : private
//	Description :
//				I. 消息队列头文件
//				III. 目前我们采用 v1.3 版的 std::list ，以后会改用 std::queue ，性能会有提升
//				IV. 消息队列会主动通知其处理线程，因此它需要继承自 subject
//
////////////////////////////////////////////////////////////////////////////////////////

#include "message_pool.h"

namespace PS_FW
{
	MessagePool::MessagePool()
	{
		if(pthread_mutex_init(&m_mxLock,NULL) == 0)
		{
			m_pPool = new Pool;
		}
	}


	MessagePool::~MessagePool()
	{
		while(!m_pPool->empty())
		{
			void* task = m_pPool->front();
			m_pPool->pop_front();
			free(task);
		}

		delete m_pPool;
		pthread_mutex_destroy(&m_mxLock);
	}


	int MessagePool::push(void* msg)
	{
		pthread_mutex_lock(&m_mxLock);
		m_pPool->push_back(msg);
		pthread_mutex_unlock(&m_mxLock);

		return 0;
	}


	int MessagePool::pushByChar(char* szMessage)
	{
		if(this->push((void*)szMessage) != 0)
		{
			return -1;
		}

		return 0;
	}


	int MessagePool::pop(void** msg)
	{
		pthread_mutex_lock(&m_mxLock);
		if(!m_pPool->empty())
		{
			*msg = m_pPool->front();
			m_pPool->pop_front();
		}
		else
		{			
			pthread_mutex_unlock(&m_mxLock);
			return -1;
		}
		pthread_mutex_unlock(&m_mxLock);

		return 0;
	}


	int MessagePool::popByChar(char* szMessage)
	{
		void* task = NULL;

		if(this->pop(&task) == 0)
		{
			szMessage = (char*)task;

			return 0;
		}

		return -1;
	}
}	//PS_FW

