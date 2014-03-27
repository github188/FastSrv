
#include "ps_socket_api.h"

int socket_create(const char* host,const unsigned short port,struct sockaddr_in& addr,int& socketfd)
{
	/* 转换IP */
	in_addr_t ipv4;
	struct hostent ret;
	char buf[1024] = {'\0'};
	struct hostent* result;
	int h_errnop;

	if(gethostbyname_r(host,&ret,buf,1024,&result,&h_errnop) != 0)
	{
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

	/* 生成socket描述符 */
	int on = 1;

	socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd == -1)
	{
		return -1;
	}
	setsockopt(socketfd,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));

	/* 生成地址 */
	memset(&addr,0,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ipv4;
	addr.sin_port = htons(port);

	return 0;
}

int socket_open(const char* host,const unsigned short port,int& socketfd)
{
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(struct sockaddr_in));

	if(socket_create(host,port,addr,socketfd) == -1)
	{
		printf("\n==============socket_create() fail");
		return -1;
	}

	/* IP、端口和socket描述符绑定 */
	if(bind(socketfd,(struct sockaddr*)&addr,sizeof(struct sockaddr)) != 0)
	{
		printf("\n==============bind() fail");
		return -1;
	}

	/* 监听 */
	if(listen(socketfd,128) != 0)
	{
		printf("\n==============listen() fail");
		return -1;
	}

	return 0;
}

int socket_accept(const int sSocketfd,int& cSocketfd)
{
	unsigned int addrlen;
	struct sockaddr addr;

	addrlen = sizeof(struct sockaddr);
	cSocketfd = accept(sSocketfd,&addr,&addrlen);

	if(cSocketfd == -1)
	{
		return -1;
	}

	return 0;
}

int socket_connect(const char* host,const unsigned short port,int& socketfd,int retry,const int sleep)
{
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(struct sockaddr_in));

	if(socket_create(host,port,addr,socketfd) == -1)
	{
		printf("\n==============socket_create() fail");
		return -1;
	}

	while(true)
	{
		if(connect(socketfd,(struct sockaddr*)&addr,sizeof(struct sockaddr)) == 0)
		{
			return 0;
		}
		else
		{
			if(retry > 0)
			{
				printf("\n==============connect() fail , retry after %d second, remain retry count is : %d",sleep,--retry);
				usleep(sleep*1000*1000);
			}
			else
			{
				return -1;
			}
		}
	}

	return 0;
}

int socket_close(int& socketfd)
{
	close(socketfd);
	socketfd = 0;

	return 0;
}

