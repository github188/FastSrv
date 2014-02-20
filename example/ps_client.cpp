/* 
** 
** client 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "../ps_api.h"
#include "ps_message.h"

int main()
{
	int socketfd;

	if(socket_open("127.0.0.1",42890,socketfd) == -1)
	{
		printf("\n==============socket_create() fail\n");
		socket_close(socketfd);
		return 0;
	}

	printf("\n==============socket_create() success\n");

	if(socket_connect("127.0.0.1",42890,socketfd,10,5) != 0)
	{
		printf("\n==============socket_connect error!\n");
		socket_close(socketfd);
		return 0;
	}

	socket_close(socketfd);

	return 0;
}

