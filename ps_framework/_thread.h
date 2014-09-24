#ifndef __PS_FW_THREAD__
#define __PS_FW_THREAD__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-19 zengpw 重新设计
//					2014-9-22 zengpw 重新设计
//					2014-9-24 zengpw 优化说明和设计
//	File Property : public
//	Description :
//					I. 提供单独启动线程的方法
//					II. 部分设计的元素是为线程池使用的
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
		explicit Thread(func_addr func,func_arg arg);
		virtual ~Thread();
	public:
		// set get 函数
		int getStatus();
		void setStatus(int st);
		int getEventStatus();
		void setEventStatus(int st);
		// wait thread
		void join();
		/*---------------------
		// attach() 注册函数，供线程池或多重回调使用
		// detach() 反注册
		// run() 运行回调
		---------------------*/
		void attach(func_addr func,func_arg arg);
		void detach();
		void callEvent();
	public:
		/*---------------------
		// m_tid 线程编号（不是整型）
		---------------------*/
		pthread_t m_tid;
	private:
		/*---------------------
		// m_status 工作状态； =0 wait ， =1 work
		// m_mxLock 线程锁
		---------------------*/
		int m_status;
		pthread_mutex_t m_mxLock;
		/*---------------------
		// m_run 是否在执行回调事件； =-1 unregist event , =0 wait ， =1 running
		// m_func 回调函数，专为线程池使用
		// m_arg 回调函数参数
		---------------------*/
		int m_event;
		func_addr m_func;
		func_arg m_arg;
	};
}	//PS_FW

#endif //__PS_FW_THREAD__
