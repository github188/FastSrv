#ifndef __PS_FW_THREAD__
#define __PS_FW_THREAD__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月22日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :
//				I. 线程
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"

namespace PS_FW
{
	class Thread
	{
	public:
		Thread();
		virtual ~Thread(){}
	public:
		virtual void OnThreadRun(){}
	public:
		pthread_t m_tid;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_THREAD__
