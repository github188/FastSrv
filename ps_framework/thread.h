#ifndef __PS_FW_THREAD__
#define __PS_FW_THREAD__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月22日 zengpw 重新设计
//					2014年9月3日 zengpw 重新设计
//	File Property : private
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
		Thread(void* (*threadCallback)(void*),void* pSubject);
		virtual ~Thread();
	public:
		pthread_t m_tid;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_THREAD__
