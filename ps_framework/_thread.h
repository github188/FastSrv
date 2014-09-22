#ifndef __PS_FW_THREAD__
#define __PS_FW_THREAD__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//	File Property : public
//	Description :
//					I. 提供单独启动线程的方法
//					II. 提供独立的元素供线程池使用
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_include.h"

namespace PS_FW
{
	typedef void*(*func_addr)(void*);
	typedef void* func_arg;

	class Thread
	{
	public:
		Thread();
		Thread(func_addr func,func_arg arg);
		virtual ~Thread();
	public:
		void join();
		int initLock();
		void destroyLock();
	public:
		/*---------------------
		// m_tid 线程编号（不是整型）
		// m_condLock 条件锁
		// m_mxLock 线程锁
		// m_func 回调函数
		// m_arg 回调函数参数
		// m_status 工作状态；=0 wait ， =1 work
		---------------------*/
		pthread_t m_tid;
		pthread_cond_t m_condLock;
		pthread_mutex_t m_mxLock;
		func_addr m_func;
		func_arg m_arg;
		int m_status;
	};
}	//PS_FW

#endif //__PS_FW_THREAD__
