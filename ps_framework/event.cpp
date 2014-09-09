////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 用于管理成功建立的 socket
//					2014年9月8日 zengpw 用于管理所有发生的事件
//					2014年9月9日 zengpw 完善服务端事件
//	File Property : private
//	Description :
//					I. 事件观察者
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "event.h"

namespace PS_FW
{
	Event::Event()
	{
		m_pConnection = NULL;
		m_pChannelServer = NULL;
		m_pChannelClient = NULL;
		m_pChannelRead = NULL;
	}

	Event::~Event()
	{
		if (m_pChannelServer != NULL)
		{
			m_pChannelServer->Detach(this);
		}
		
		if (m_pChannelClient != NULL)
		{
			m_pChannelClient->Detach(this);
		}

		if (m_pChannelRead != NULL)
		{
			m_pChannelRead->Detach(this);
		}
	}


	int Event::AttachConnection(Connection* pConnection)
	{
		m_pConnection = pConnection;
		m_pChannelServer = m_pConnection->m_pChannelServer;
		m_pChannelServer->Attach(this);
		m_pChannelClient = m_pConnection->m_pChannelClient;
		m_pChannelClient->Attach(this);
		m_pChannelRead = m_pConnection->m_pChannelRead;
		m_pChannelRead->Attach(this);

		return 0;
	}


	int Event::AttachSession(Session* pSession)
	{
		m_pSession = pSession;

		return 0;
	}


	void Event::Update(Subject* pSubject)
	{
		if(pSubject == m_pChannelServer)
		{
			//如果是 Server 发出了通知
			printf("\n[PS_FW::Event]: receive notify from server channel , m_sockP = %d ! \n",m_pChannelServer->m_sockP);
			m_pConnection->read(m_pChannelServer->m_sockP);
			m_pConnection->send(m_pChannelServer->m_sockP);
		}
		else if(pSubject == m_pChannelClient)
		{
			printf("\n[PS_FW::Event]: receive notify from client channel m_sockP = %d ! \n",m_pChannelClient->m_sockP);
			m_pConnection->read(m_pChannelClient->m_sockP);
			m_pConnection->send(m_pChannelClient->m_sockP);
		}
		else if(pSubject == m_pChannelRead)
		{
			printf("\n[PS_FW::Event]: receive notify from read channel m_sockP = %d ! \n",m_pChannelRead->m_sockP);
		}
		else
		{
			printf("\n[PS_FW::Event]: unknown subject notify ! \n");
		}
	}
}	//PS_FW

