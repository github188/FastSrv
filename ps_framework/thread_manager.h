#ifndef __PS_FW_THREAD_MANAGER__
#define __PS_FW_THREAD_MANAGER__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 创建
//	File Property : private
//	Description :
//					I. 管理线程
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "thread.h"
#include "channel.h"

namespace PS_FW
{
	class ThreadManager
	{
	public:
		ThreadManager();
		ThreadManager(Channel* pChannel);
		virtual ~ThreadManager(){}
	public:
		/* 监听线程 */
		int openListenThread(const char* ip,const int port);
		/* 客户端线程 */
		int openConnThread(const char* ip,const int port);
		/* 注册 Channel */
		int attach(Channel* pChannel);
		/* 等待所有线程返回 */
		int join();
	public:
		char m_szIP[64];
		int m_port;
	public:
		Thread* m_pThreadListen;
		Channel* m_pChannel;
	};
}	//PS_FW

#endif //__PS_FW_THREAD_MANAGER__
