/* 
** 
** server 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "../ps_api.h"
#include "ps_message.h"

int event_logout(int cSocketfd);
int event_deal(int cSocketfd);
int event_login(int cSocketfd);
int event(int cSocketfd);

int main()
{
	while(true)
	{
		int socketfd;

		if(socket_open("127.0.0.1",42890,socketfd) != 0)
		{
			printf("\n==============socket_listen error!");
			continue;
		}

		printf("\n==============service socket is : %d\n",socketfd);

		wait_use_select(socketfd,event);
		socket_close(socketfd);
	}

	return 0;
}

int event(int cSocketfd)
{
	printf("\n==============client connect! client socket is : %d",cSocketfd);

	printf("\n==============I will authenticate the client.");	
	if(event_login(cSocketfd) != 0)
	{
		return -1;
	}

	printf("\n==============Begin the deal.");	
	if(event_deal(cSocketfd) != 0)
	{
		return -1;
	}

	printf("\n==============Client logout.");	
	if(event_logout(cSocketfd) != 0)
	{
		return -1;
	}

	return 0;
}

int event_login(int cSocketfd)
{
	//to do...
	return 0;
}

int event_deal(int cSocketfd)
{
	//to do...
	return 0;
}

int event_logout(int cSocketfd)
{
	//to do...
	return 0;
}

