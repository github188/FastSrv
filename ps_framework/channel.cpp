////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月2日 zengpw 重新设计
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
		m_pChannelImp->init();
	}


	Channel::~Channel()
	{
		delete m_pChannelImp;
		delete m_pChannelImpFactory;
	}


	int Channel::acceptConn(const char* ip,const int port)
	{
		if(m_pChannelImp->acceptConnInit(ip,port,m_sockS) == 0)
		{
			while (true)
			{
				printf("\n[PS_FW::Channel]: acceptConnWait begin ! \n");
				if (m_pChannelImp->acceptConnWait(m_sockS) == 0)
				{
					printf("\n[PS_FW::Channel]: acceptConnWait ok ! \n");
					if (m_pChannelImp->acceptConn(m_sockS,m_sockP) == 0)
					{
						//通知 socket manager
						Notify();
						printf("\n[PS_FW::Channel]: get client socket ! \n");
						printf("\n[PS_FW::Channel]: now notify SocketManager ! \n");
					}
				}
				printf("\n[PS_FW::Channel]: acceptConnWait end ! \n");
			}
		}
		else
		{
			return -1;
		}

		return 0;
	}

	int Channel::conn(const char* ip,const int port)
	{
		if (m_pChannelImp->conn(ip,port,m_sockP) == 0)
		{
			//通知 socket manager
			Notify();
			printf("\n[PS_FW::Channel]: get server socket ! \n");
			printf("\n[PS_FW::Channel]: now notify SocketManager ! \n");
		}
		else
		{
			return -1;
		}

		return 0;
	}

	int Channel::recvData(const int sockId,char* rBuf,int& rlen,Protocol* pProtocol)
	{
		char szBuf[10240];
		int pos = 0;
		memset(szBuf,'\0',10240);

		while( m_pChannelImp->recvData(sockId,szBuf,10240,pos) == 0)
		{
			/* 如果包读取没有问题，就写数据区 */
			memcpy(m_pData + m_pos,szBuf,pos);
			m_pos += pos;

			/* 送给 protocol 进行校验 */
			int flag = 0;
			int pos = 0;
			// flag 取值： 1（整包） || 2（整包 + 部分包） || 3（部分包） || 4（错误包）
			// pos 当 flag = 2 时，返回 包偏移地址
			pProtocol->verifyPacket(m_pData,m_pData + m_pos,flag,pos);

			if(flag == 1)
			{
				rlen = m_pos;
				memcpy(rBuf,m_pData,rlen);
				/* 最简单的情况，清空当前数据区即可 */
				memset(m_pData,'\0',30960);

				return 0;
			}
			else if (flag == 2)
			{
				rlen = pos;
				memcpy(rBuf,m_pData,rlen);
				/* 将当前数据区数据未读取的部分，存储到 Next 数据区，然后 Current 和 Next 指针交换 */
				/* Next 数据区将在下次发生交换时被清空 */
				memset(m_pDataNext,'\0',30960);
				memcpy(m_pDataNext,m_pData + pos,m_pos - pos);
				char* m_pDataTemp = m_pData;
				m_pData = m_pDataNext;
				m_pDataNext = m_pDataTemp;

				return 0;
			}
			else if (flag == 3)
			{
				int pos = 0;
				memset(szBuf,'\0',10240);
				continue;
			}
			else if (flag == 4)
			{
				/* 如果出错了，则清空2个数据区，这是最保守的做法 */
				memset(m_pData,'\0',30960);
				memset(m_pDataNext,'\0',30960);

				return -1;
			}
			else
			{
				return -1;
			}
		}

		return 0;
	}

	int Channel::sendData(const int sockId,const char* sBuf,const int slen)
	{
		return m_pChannelImp->sendData(sockId,sBuf,slen);
	}
}	//PS_FW
