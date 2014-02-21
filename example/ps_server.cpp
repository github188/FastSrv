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

		wait_use_select(socketfd,event);
		socket_close(socketfd);
	}

	return 0;
}

int event(int cSocketfd)
{
	printf("\n==============client connect! client socket is : %d",cSocketfd);

	if(event_login(cSocketfd) != 0)
	{
		return -1;
	}

	if(event_deal(cSocketfd) != 0)
	{
		return -1;
	}

	if(event_logout(cSocketfd) != 0)
	{
		return -1;
	}

	return 0;
}

int event_login(int cSocketfd)
{
	st_head sth;
	socket_recv_normal(cSocketfd,(char*)&sth,sizeof(st_head));

	printf("\n==============receive sth.auth : %s",sth.auth);
	printf("\n==============receive sth.version : %s",sth.version);

	if(strncmp(sth.auth,"zengpw",10) || strncmp(sth.version,"0.1",10))
	{
		printf("\n==============identity verify error!");
		return -1;
	}

	printf("\n==============client is login");

	return 0;
}

int event_deal(int cSocketfd)
{
	printf("\n==============Begin the deal.");
	//to do...
	return 0;
}

int event_logout(int cSocketfd)
{
	printf("\n==============Client logout.");
	//to do...
	return 0;
}

