////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 framework 入口
//					2014年9月3日 zengpw 增加线程管理
//					2014年9月7日 zengpw 修改（缩小） app 能持有的类对象
//	File Property : public
//	Description :	I.调用 framework 的入口
//					II.可以调用 App 的 public 方法，来启动服务器或者客户端
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_app.h"
#include "sys_include.h"
#include "event.h"
#include "connection.h"

namespace PS_FW
{
	App::App()
	{
		m_pProtocol = new Protocol;
		m_pSession = new Session;
		m_pConnection = new Connection;
		m_pConnection->setProtocol(m_pProtocol);
		m_pConnection->setSession(m_pSession);

		m_pEvent = new Event;
		m_pEvent->AttachConnection(m_pConnection);
		m_pEvent->AttachSession(m_pSession);
	}


	App::~App()
	{
		//TODO: 需要考虑如何安全的销毁APP及其所持有的对象，目前不做任何处理
	}


	int App::server(const char* ip,const int port)
	{
		return m_pConnection->server(ip,port);
	}


	int App::client(const char* ip,const int port)
	{
		return m_pConnection->client(ip,port);
	}


	void App::join()
	{
		return m_pConnection->join();
	}
}	//PS_FW
