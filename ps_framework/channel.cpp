////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月2日 zengpw 重新设计
//					2014年9月7日 zengpw 增加线程入口函数
//					2014年9月9日 zengpw 增加读数据到达通知
//	File Property : private
//	Description :	I. Channel 被设计为不持有任何数据，不管理任何对象或事务的生命周期
//					II. Channel层的下级或者同级层，都不具有回调，所有的回调收敛在 Channel
//					III. Channel 有2种用途： 建立连接 或者 接收/发送数据
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "channel.h"

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


	int Channel::setProtocol(Protocol* pProtocol)
	{
		m_pProtocol = pProtocol;

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
		if (m_pProtocol == NULL)
		{
			m_pProtocol = new Protocol;
		}

		char szBuf[10240];
		int read = 0;

		while(1)
		{
			memset(szBuf,'\0',10240);
			memset(m_szRecvData,'\0',30960);
			m_RecvLen = 0;

			if(m_pChannelImp->recvData(m_sockD,szBuf,10240,read) == 0)
			{
				/* 如果包读取没有问题，就写数据区 */
				memcpy(m_pData + m_pos,szBuf,read);
				m_pos += read;

				/* 送给 protocol 进行校验 */
				int flag = 0;
				int pos = 0;
				// flag 取值： 1（整包） || 2（整包 + 部分包） || 3（部分包） || 4（错误包）
				// pos 当 flag = 2 时，返回 包偏移地址
				m_pProtocol->verifyPacket(m_pData,m_pData + m_pos,flag,pos);

				if(flag == 1)
				{
					m_RecvLen = m_pos;
					memcpy(m_szRecvData,m_pData,m_RecvLen);
					/* 最简单的情况，清空当前数据区，将缓存的位移置0 */
					memset(m_pData,'\0',30960);
					m_pos = 0;

					//通知 event
					Notify();
				}
				else if (flag == 2)
				{
					m_RecvLen = pos;
					memcpy(m_szRecvData,m_pData,m_RecvLen);
					/* 将当前数据区数据未读取的部分，存储到 Next 数据区，然后 Current 和 Next 指针交换 */
					/* Next 数据区将在下次发生交换时被清空 */
					memset(m_pDataNext,'\0',30960);
					memcpy(m_pDataNext,m_pData + pos,m_pos - pos);
					char* m_pDataTemp = m_pData;
					m_pData = m_pDataNext;
					m_pDataNext = m_pDataTemp;

					//通知 event
					Notify();
				}
				else if (flag == 3)
				{
					memset(szBuf,'\0',10240);

					printf("\n[PS_FW::Channel]: call m_pProtocol->verifyPacket fail return falg = 3 ! \n");
					continue;
				}
				else if (flag == 4)
				{
					/* 将缓存的位移置0 */
					m_pos = 0;
					/* 如果出错了，则清空2个数据区，这是最保守的做法 */
					memset(m_pData,'\0',30960);
					memset(m_pDataNext,'\0',30960);

					printf("\n[PS_FW::Channel]: call m_pProtocol->verifyPacket fail return falg = 4 ! \n");
					continue;
				}
				else
				{
					/* 实际上不允许发生 */
					/* 将缓存的位移置0 */
					m_pos = 0;
					/* 如果出错了，则清空2个数据区，这是最保守的做法 */
					memset(m_pData,'\0',30960);
					memset(m_pDataNext,'\0',30960);
					printf("\n[PS_FW::Channel]: call m_pProtocol->verifyPacket fail return falg = unknown ! \n");
					continue;
				}
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
