////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 framework 入口
//	File Property : public
//	Description :	I.调用 framework 的入口
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "ps_fw_app.h"
#include "sys_include.h"
#include "channel.h"
#include "socket_manager.h"

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

		return 0;
	}


	int App::startServer(const char* ip,const int port)
	{
		m_pChannel->acceptConn(ip,port);

		return 0;
	}


	int App::startConn(const char* ip,const int port)
	{
		m_pChannel->conn(ip,port);

		return 0;
	}
}	//PS_FW
