#ifndef __PS_FW_CHANNEL_IMP_WIN__
#define __PS_FW_CHANNEL_IMP_WIN__
#ifdef _MSC_VER
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月1日 zengpw 添加实现
//					2014年9月2日 zengpw 添加实现
//	File Property : private
//	Description : 
//				I. ChannelImpWin 负责 Windows 下面的 socket 连接
//				II.继承自抽象类 ChannelImp 并完成该类在 Windows 下面的实现
//				III.可以参考 ChannelImp 了解函数作用
//				IV.为了避免源文件膨胀，将实现写在 .h 里
//
////////////////////////////////////////////////////////////////////////////////////////

#include "channel_imp.h"

namespace PS_FW
{
	class ChannelImpWin : public PS_FW::ChannelImp
	{
	public:
		ChannelImpWin(){};
		virtual ~ChannelImpWin(){};
	public:
		void init()
		{
			//定义使用的WinSock版本
			WSAData wsadata;
			if(WSAStartup(MAKEWORD(2,0),&wsadata) != 0)
			{
				printf("\n[PS_FW::ChannelImpWin]: WSAStartup failed with error \n");
			}

			printf("\n[PS_FW::ChannelImpWin]: init() ok ! \n");
		}


		void close(int& sockfd)
		{
			closesocket(sockfd);
			//清理
			if(WSACleanup() == SOCKET_ERROR)
			{
				printf("\n[PS_FW::ChannelImpWin]: WSACleanup failed with error %d \n",WSAGetLastError());
			}

			printf("\n[PS_FW::ChannelImpWin]: close() ok ! \n");
		}


		int acceptConnInit(const char* ip,const int port,int& sockId)
		{
			unsigned long ipv4;
			ipv4 = inet_addr(ip);
			//填充sockaddr_in结构
			SOCKADDR_IN sAddr;
			sAddr.sin_family = AF_INET;
			sAddr.sin_addr.s_addr = ipv4;
			sAddr.sin_port = htons(port);

			//初始化socket
			SOCKET s;
			s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

			//bind
			bind(s,(SOCKADDR*)&sAddr,sizeof(SOCKADDR));

			/* 监听 */
			if(listen(s,128) != 0)
			{
				printf("\n[PS_FW::ChannelImpWin]: listen() fail \n");
				return -1;
			}

			sockId = (int)s;

			printf("\n[PS_FW::ChannelImpWin]: acceptConnInit() ok ! \n");
			printf("\n[PS_FW::ChannelImpWin]: listen on %s:%d now ! \n",ip,port);

			return 0;
		}


		int acceptConnWait(const int sockId)
		{
			fd_set fdread;

			FD_ZERO(&fdread);
			FD_SET(sockId,&fdread);
			int ret = select(0,&fdread,NULL,NULL,NULL);

			if(ret > 0)
			{
				if(FD_ISSET(sockId,&fdread))
				{
					printf("\n[PS_FW::ChannelImpWin]: acceptConnWait() ok ! \n");
					return 0;
				}
			}

			printf("\n[PS_FW::ChannelImpWin]: acceptConnWait() fail ! \n");
			return -1;
		}


		int acceptConn(const int sockId,int& sockPeerId)
		{
			int len;
			SOCKADDR_IN sAddr;
			SOCKET s;

			s = accept(sockId,(SOCKADDR*)&sAddr,&len);

			sockPeerId = (int)s;

			printf("\n[PS_FW::ChannelImpWin]: acceptConn() ok ! \n");
			return 0;
		}


		int conn(const char* ip,const int port,int& sockPeerId)
		{
			unsigned long ipv4;
			ipv4 = inet_addr(ip);
			//填充sockaddr_in结构
			SOCKADDR_IN sAddr;
			sAddr.sin_family = AF_INET;
			sAddr.sin_addr.s_addr = ipv4;
			sAddr.sin_port = htons(port);

			//初始化socket
			SOCKET s;
			s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

			int retry = 5;
			int sleep = 3;

			while(true)
			{
				printf("\n[PS_FW::ChannelImpWin]: connect to %s:%d now ! \n",ip,port);
				if(connect(s,(SOCKADDR*)&sAddr,sizeof(SOCKADDR)) == 0)
				{
					sockPeerId = (int)s;
					printf("\n[PS_FW::ChannelImpWin]: conn() ok ! \n");
					return 0;
				}
				else
				{
					if(retry > 0)
					{
						PS_FW::SYS_FUNC::sleep(3000);
						printf("\n[PS_FW::ChannelImpWin]: connect() fail , retry after %d second, remainder %d \n",sleep,--retry);
					}
					else
					{
						return -1;
					}
				}
			}

			return 0;
		}


		int recvData(const int sockId,char* szBuf,const int len,int& realLen)
		{
			realLen = 0;

			while((len - realLen) > 0)
			{
				int received = 0;
				received = (int)recv(sockId,szBuf + realLen,len - realLen,0);
				if( received <= 0 )
				{
					return -1;
				}
				realLen += received;
			}

			return 0;
		}


		int sendData(const int sockId,const char* szBuf,const int len)
		{
			int realSend = 0;

			while((len - realSend) > 0)
			{
				int sent = 0;
				sent = (int)send(sockId,szBuf + realSend,len - realSend,0);
				if(sent <= 0)
				{
					return -1;
				}
				realSend += sent;
			}

			return 0;
		}
	};	//ChannelImpWin
}	//PS_FW

#endif //_MSC_VER
#endif //__PS_FW_CHANNEL_IMP_WIN__

