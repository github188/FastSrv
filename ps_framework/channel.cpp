////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-2 zengpw 重新设计
//					2014-9-7 zengpw 增加线程入口函数
//					2014-9-9 zengpw 增加读数据到达通知
//					2014-9-10 zengpw 将 Channel 和 Protocol 解耦
//					2014-9-18 zengpw 将 Channel 与 Thread 解耦，以后需要通过继承来使用 Channel
//	File Property : public
//	Description :	
//					I. Channel 被设计为不持有任何数据，不管理任何对象或事务的生命周期
//					II. Channel层的下级或者同级层，都不具有回调，所有的回调收敛在 Channel
//					III. Channel 有2种用途： 建立连接 或者 接收/发送数据
//	Future :
//					I. 实现异步和非阻塞
//					II. 增加一个成员变量，方便观察者判断 Channel 的事件性质
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "channel.h"
#include "_include.h"
#include "sys_func.h"
#include "channel_imp_factory.h"

namespace PS_FW
{
	Channel::Channel()
	{
		m_pChannelImpFactory = new ChannelImpFactory;
		m_pChannelImp = m_pChannelImpFactory->create();
	}


	Channel::~Channel()
	{
		delete m_pChannelImp;
		delete m_pChannelImpFactory;
	}


	int Channel::setAddress(const char* ip,const int port)
	{
		strncpy(m_szIP,ip,128);
		m_port = port;

		return 0;
	}


	int Channel::setSocket(const int sockId)
	{
		m_sockD = sockId;

		return 0;
	}


	int Channel::acceptConn()
	{
		m_pChannelImp->init();

		if(m_pChannelImp->acceptConnInit(m_szIP,m_port,m_sockS) == 0)
		{
			while (true)
			{
				printf("\n[PS_FW::Channel]: m_sockS is %d , acceptConnWait begin ! \n",m_sockS);
				if (m_pChannelImp->acceptConnWait(m_sockS) == 0)
				{
					printf("\n[PS_FW::Channel]: new socket coming ! \n");
					if (m_pChannelImp->acceptConn(m_sockS,m_sockP) == 0)
					{
						printf("\n[PS_FW::Channel]: new socket accept success ! \n");
						printf("\n[PS_FW::Channel]: m_sockS is %d , m_sockP is %d ! \n",m_sockS,m_sockP);
						//通知 event
						Notify();
					}
					else
					{
						printf("\n[PS_FW::Channel]: new socket accept fail ! \n");
						PS_FW::SYS_FUNC::sleep(3000);
					}
				}
			}
		}
		else
		{
			return -1;
		}

		return 0;
	}


	void* Channel::acceptConnThread(void* pChannel)
	{
		Channel* p = (Channel*)pChannel;
		p->acceptConn();

		return NULL;
	}


	int Channel::conn()
	{
		m_pChannelImp->init();

		if (m_pChannelImp->conn(m_szIP,m_port,m_sockP) == 0)
		{
			printf("\n[PS_FW::Channel]: conn success ! \n");
			Notify();
		}
		else
		{
			return -1;
		}

		return 0;
	}


	void* Channel::connThread(void* pChannel)
	{
		Channel* p = (Channel*)pChannel;
		p->conn();

		return NULL;
	}


	int Channel::recvData()
	{
		while(1)
		{
			m_RecvLen = 0;
			memset(m_szRecvData,'\0',30960);

			if(m_pChannelImp->recvData(m_sockD,m_szRecvData,30960,m_RecvLen) == 0)
			{
				//通知 event
				Notify();
			}
		}

		return 0;
	}


	void* Channel::recvDataThread(void* pChannel)
	{
		Channel* p = (Channel*)pChannel;
		p->recvData();

		return NULL;
	}


	int Channel::sendData(const char* szBuf,const int len)
	{
		return m_pChannelImp->sendData(m_sockD,szBuf,len);
	}
}	//PS_FW
