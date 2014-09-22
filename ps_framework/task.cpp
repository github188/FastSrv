////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-18 zengpw 重新设计
//	File Property : private
//	Description :
//					I. 消息队列头文件
//					II. 采用 queue 做容器
//					III. 它提供的接口中，task 是基础数据类型（因为内部要支持free()函数）
//	Future :
//					I. 提供双队列（输入和输出）
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "task.h"

namespace PS_FW
{
	Task::Task()
	{
		if(pthread_mutex_init(&m_queueLock,NULL) == 0)
		{
			m_queue = new std::queue<void*>;
		}
	}


	Task::~Task()
	{
		while(!m_queue->empty())
		{
			void* task = m_queue->front();
			m_queue->pop();
			free(task);
		}

		delete m_queue;
		pthread_mutex_destroy(&m_queueLock);
	}


	int Task::push(void* task)
	{
		pthread_mutex_lock(&m_queueLock);
		m_queue->push(task);
		pthread_mutex_unlock(&m_queueLock);

		return 0;
	}


	int Task::pop(void** task)
	{
		pthread_mutex_lock(&m_queueLock);
		if(!m_queue->empty())
		{
			*task = m_queue->front();
			m_queue->pop();
		}
		pthread_mutex_unlock(&m_queueLock);

		return 0;
	}
}	//PS_FW

