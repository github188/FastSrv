////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :
//				I. 任务队列头文件
//				II.  接收队列由 IO 线程 put ，处理线程 get ，发送队列只由 处理线程 put
//				III. 目前我们采用 v1.3 版的 std::list ，以后会改用 std::queue ，性能会有提升
//
////////////////////////////////////////////////////////////////////////////////////////

#include "msg_queue.h"

namespace PS_FW
{
	MsgQueue::MsgQueue()
	{
		m_queue = new MsgList;

		if(pthread_mutex_init(&m_mxLock,NULL))
		{
			destory();
		}
	}


	int MsgQueue::put(void* msg)
	{
		pthread_mutex_lock(&m_mxLock);
		m_queue->push_back(msg);
		pthread_mutex_unlock(&m_mxLock);
		Notify();

		return 0;
	}


	int MsgQueue::get(void** msg)
	{
		pthread_mutex_lock(&m_mxLock);
		if(!m_queue->empty())
		{
			*msg = m_queue->front();
			m_queue->pop_front();
		}
		else
		{			
			pthread_mutex_unlock(&m_mxLock);
			return -1;
		}
		pthread_mutex_unlock(&m_mxLock);

		return 0;
	}


	int MsgQueue::destory()
	{
		while(!m_queue->empty())
		{
			void* task = m_queue->front();
			m_queue->pop_front();
			/* 有待改进 */
			free(task);
		}

		delete m_queue;

		pthread_mutex_destroy(&m_mxLock);

		return 0;
	}
}	//PS_FW


