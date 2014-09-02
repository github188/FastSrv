#ifndef __PS_FW_THREAD_POOL_DEAL__
#define __PS_FW_THREAD_POOL_DEAL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw add
//	File Property : private （此头文件是私有的）
//	Description :
//				I. 处理线程池
//				II. 线程池观察消息队列上发生的 put 事件，当 put 发生时，会通知线程池，
//					线程池收到通知以后，会从消息队列取数据
//				III. 要使线程池具有观察者功能，它需要继承自 EventObserver
//
////////////////////////////////////////////////////////////////////////////////////////

#include "thread_pool.h"
#include "msg_queue.h"
#include "subject.h"
#include "observer.h"

namespace PS_FW
{
	class ThreadPoolDeal : public ThreadPool , public Observer
	{
	public:
		ThreadPoolDeal::ThreadPoolDeal(int size,MsgQueue* pMsgQueue) : ThreadPool(size)
		{
			m_pMsgQueue = pMsgQueue;
			m_pMsgQueue->Attach(this);
		}

		ThreadPoolDeal::~ThreadPoolDeal()
		{
			m_pMsgQueue->Detach(this);
		}

		virtual void ThreadPoolDeal::Update(Subject* pSubject)
		{
			if(m_pMsgQueue == pSubject)
			{
				//TODO
			}
		}
	private:
		MsgQueue* m_pMsgQueue;
	};
}	//PS_FW

#endif //__PS_FW_THREAD_POOL_DEAL__

