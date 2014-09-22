#ifndef __PS_FW_THREAD_POOL__
#define __PS_FW_THREAD_POOL__
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

#include "_include.h"
#include "_thread.h"

namespace PS_FW
{
	class ThreadPool
	{
	public:
		explicit ThreadPool(int size);
		virtual ~ThreadPool();
	public:
		int add(func_addr func,func_arg arg);
		void destroy();
	private:
		bool isEmpty(void* pool);
		static void* loop(void* pool);
	private:
		/*---------------------
		// m_count 线程池引用计数
		// m_status 线程池状态；=0 close ， =1 open
		// m_vcThread 池内的线程
		// m_mxLock 池锁
		---------------------*/
		int m_count;
		int m_status;
		std::vector<Thread*> m_vcThread;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_THREAD_POOL__
