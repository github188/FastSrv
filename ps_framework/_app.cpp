////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 framework 入口
//					2014年9月3日 zengpw 增加线程管理
//	File Property : public
//	Description :	I.调用 framework 的入口
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "_app.h"
#include "channel.h"
#include "socket_manager.h"
#include "thread_manager.h"

namespace PS_FW
{
	App::App()
	{
		this->init();
	}

	int App::init()
	{
		//声明用于监听连接或主动连接的 Channel
		m_pChannel =  new Channel;
		//声明 Channel 的观察者
		m_pSocketManager = new SocketManager(m_pChannel);
		//声明 ThreadManager ，并注册这个 Channel
		m_pThreadManager = new ThreadManager(m_pChannel);
		return 0;
	}


	int App::startServer(const char* ip,const int port)
	{
		return m_pThreadManager->openListenThread(ip,port);
	}


	int App::startConn(const char* ip,const int port)
	{
		return m_pThreadManager->openConnThread(ip,port);
	}


	int App::join()
	{
		return m_pThreadManager->join();
	}
}	//PS_FW
