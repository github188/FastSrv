#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

int socket_open(const char* host,unsigned short port)
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
	int theSocket;
	int on = 1;

	theSocket = socket(AF_INET,SOCK_STREAM,0);
	if(theSocket == -1)
	{
		printf("\n==============socket() fail");
		return -1;
	}
	setsockopt(theSocket,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));

	/* IP、端口和socket描述符绑定 */
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ipv4;
	addr.sin_port = htons(port);
	if(bind(theSocket,(struct sockaddr*)&addr,sizeof(struct sockaddr)) != 0)
	{
		printf("\n==============bind() fail");
		return -1;
	}

	/* 监听 */
	if(listen(theSocket,128) != 0)
	{
		printf("\n==============bind() fail");
		return -1;
	}

	return theSocket;
}

int socket_accept(int serverSocket)
{
	unsigned int addrlen;
	struct sockaddr clientAddr;

	addrlen = sizeof(struct sockaddr);

	return accept(serverSocket,&clientAddr,&addrlen);
}

