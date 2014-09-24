#ifndef __PS_FW_THREAD_POOL__
#define __PS_FW_THREAD_POOL__
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
	private:
		static void* loop(void* pool);
	private:
		/*---------------------
		// m_st 线程池状态； =0 close ， =1 open
		// m_count 线程池引用计数
		// m_condLock 条件变量
		// m_lock 池锁
		// pThread 指向刚刚创建的那个线程
		// m_vcThread 池内的线程
		---------------------*/
		int m_st;
		int m_count;
		pthread_cond_t m_condLock;
		pthread_mutex_t m_lock;
		std::vector<Thread*> m_vcThread;
	};
}	//PS_FW

#endif //__PS_FW_THREAD_POOL__
