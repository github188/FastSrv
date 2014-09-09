////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 连接管理
//					2014年9月7日 zengpw 添加实现
//					2014年9月9日 zengpw 规范注释，添加处理线程
//	File Property : private
//	Description :
//					I.这个类的对象的生命周期是全局的，随着进程退出而消亡
//					Ⅱ.它拥有 主动连接 和 被动连接 2种方式
//					Ⅲ.它直接持有 Channel 对象
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "connection.h"

namespace PS_FW
{
	Connection::Connection()
	{
		m_pChannelServer = new Channel;
		m_pChannelClient = new Channel;
		m_pChannelRead = new Channel;
		m_pChannelSend = new Channel;
	}

	Connection::~Connection()
	{
		delete m_pChannelServer;
		delete m_pChannelClient;
		delete m_pChannelRead;
		delete m_pChannelSend;
	}


	int Connection::setProtocol(Protocol* pProtocol)
	{
		m_pProtocol = pProtocol;

		return 0;
	}


	int Connection::setSession(Session* pSession)
	{
		m_pSession = pSession;

		return 0;
	}


	int Connection::server(const char* ip,const int port)
	{
		m_pChannelServer->setAddress(ip,port);
		run(Channel::acceptConnThread,m_pChannelServer);

		return 0;
	}


	int Connection::client(const char* ip,const int port)
	{
		m_pChannelClient->setAddress(ip,port);
		run(Channel::connThread,m_pChannelClient);

		return 0;
	}


	int Connection::read(const int sockId)
	{
		m_pChannelRead->setSocket(sockId);
		m_pChannelRead->setProtocol(m_pProtocol);
		run(Channel::recvDataThread,m_pChannelRead);

		return 0;
	}


	int Connection::send(const int sockId)
	{
		m_pChannelSend->setSocket(sockId);
		run(Connection::dealThread,this);

		return 0;
	}


	void* Connection::dealThread(void* pConnection)
	{
		Connection* p = (Connection*)pConnection;

		char szMessage[10240];
		int len;

		while (1)
		{
			memset(szMessage,'\0',10240);
			len = 0;

			p->m_pSession->setMessageIn("ps_framework logon");
			p->m_pSession->dealMessage();
			p->m_pSession->getMessageOut(szMessage,len);
			p->m_pChannelSend->sendData(szMessage,len);
		}

		return NULL;
	}
}	//PS_FW

