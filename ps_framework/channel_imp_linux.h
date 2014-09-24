#ifndef __PS_FW_CHANNEL_IMP_LINUX__
#define __PS_FW_CHANNEL_IMP_LINUX__
#ifdef __GNU_C__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月2日 zengpw 重新修改实现
//	File Property : private
//	Description : 
//					I. ChannelImpLinux 负责 Linux 下面的 socket 连接
//					II.继承自抽象类 ChannelImp 并完成该类在 Linux 下面的实现
//					III.可以参考 ChannelImp 了解函数作用
//					IV.为了避免源文件膨胀，将实现写在 .h 里
//
////////////////////////////////////////////////////////////////////////////////////////

#include "channel_imp.h"

namespace PS_FW
{
	class ChannelImpLinux : public PS_FW::ChannelImp
	{
	public:
		ChannelImpLinux(){};
		virtual ~ChannelImpLinux(){};
	public:
		void init()
		{
			printf("\n[ps_fw_framework] socket init success!");
		}


		void close(int& sockfd)
		{
			close(sockfd);
			sockfd = 0;
			printf("\n[ps_fw_framework] socket close success!");
		}


		int acceptConnInit(const char* ip,const int port,int& sockId)
		{
			/* 转换IP */
			char buf[1024] = {'\0'};
			in_addr_t ipv4;
			struct hostent ret;
			struct hostent* result;
			int h_errnop;

			if(gethostbyname_r(ip,&ret,buf,1024,&result,&h_errnop) != 0)
			{
				printf("\n[ps_fw_framework] gethostbyname_r() fail");
				herror("gethostbyname_r() fail :");
				ipv4 = inet_addr(host);
			}
			else
			{
				ipv4 = *(int*)(*result).h_addr_list[0];
			}

			if(ipv4 == INADDR_NONE)
			{
				return -1;
			}

			/* 设置 sockaddr_in */
			struct sockaddr_in sAddrIn;
			memset(&sAddrIn,0,sizeof(struct sockaddr_in));
			sAddrIn.sin_family = AF_INET;
			sAddrIn.sin_addr.s_addr = ipv4;
			sAddrIn.sin_port = htons(port);

			/* 设置 socket fd */
			int s = socket(AF_INET,SOCK_STREAM,0);
			if(s == -1)
			{
				return -1;
			}

			int on = 1;
			setsockopt(s,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));

			/* IP、端口和socket描述符绑定 */
			if(bind(s,(struct sockaddr*)&sAddrIn,sizeof(struct sockaddr)) != 0)
			{
				printf("\n[ps_fw_framework] bind() fail");
				return -1;
			}

			/* 监听 */
			if(listen(s,128) != 0)
			{
				printf("\n[ps_fw_framework] listen() fail");
				return -1;
			}

			sockId = s;

			printf("\n[ps_fw_framework] listen on %s:%d success",ip,port);

			return 0;
		}


		int acceptConnWait(const int sockId)
		{
			//用 select 轮询
			fd_set fd;
			struct timeval tv;

			tv.tv_sec = 0;
			tv.tv_usec = 100000;
			FD_ZERO(&fd);
			FD_SET(sfd,&fd);

			if(select(sockId+1,&fd,NULL,NULL,&tv) > 0)
			{
				return 0;
			}

			return -1;
		}


		int acceptConn(const int sockId,int& sockPeerId)
		{
			unsigned int addrlen;
			struct sockaddr addr;

			addrlen = sizeof(struct sockaddr);
			sockPeerId = accept(sockId,&addr,&addrlen);

			return 0;
		}


		int conn(const char* ip,const int port,int& sockPeerId)
		{
			/* 转换IP */
			char buf[1024] = {'\0'};
			in_addr_t ipv4;
			struct hostent ret;
			struct hostent* result;
			int h_errnop;

			if(gethostbyname_r(ip,&ret,buf,1024,&result,&h_errnop) != 0)
			{
				printf("\n[ps_fw_framework] gethostbyname_r() fail");
				herror("gethostbyname_r() fail :");
				ipv4 = inet_addr(host);
			}
			else
			{
				ipv4 = *(int*)(*result).h_addr_list[0];
			}

			if(ipv4 == INADDR_NONE)
			{
				return -1;
			}

			/* 设置 sockaddr_in */
			struct sockaddr_in sAddrIn;
			memset(&sAddrIn,0,sizeof(struct sockaddr_in));
			sAddrIn.sin_family = AF_INET;
			sAddrIn.sin_addr.s_addr = ipv4;
			sAddrIn.sin_port = htons(port);

			int s = socket(AF_INET,SOCK_STREAM,0);
			if(s == -1)
			{
				return -1;
			}

			int retry = 5;
			int sleep = 3;

			while(true)
			{
				memset(&sAddrIn,0,sizeof(struct sockaddr_in));

				if(connect(s,(struct sockaddr*)&sAddrIn,sizeof(struct sockaddr)) == 0)
				{
					sockPeerId = s;
					return 0;
				}
				else
				{
					if(retry > 0)
					{
						printf("\n[ps_fw_framework] connect() fail , retry after %d second, remain retry count is : %d",sleep,--retry);
						PS_FW::SYS_FUNC::sleep(sleep);
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
	};
}	//PS_FW

#endif //__GNU_C__
#endif //__PS_FW_CHANNEL_IMP_LINUX__

