
#include "ps_socket_api.h"

void wait_use_select(int socketfd,int(*event)(int))
{
	fd_set fd;
	struct timeval tv;

	/* 等待连接次数 */
	int count = 0;

	while(true)
	{
		printf("\nread ==============this is the %dth call select()",++count);

		FD_ZERO(&fd);
		FD_SET(socketfd,&fd);
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		if(select(socketfd+1,&fd,NULL,NULL,&tv) <= 0)
		{
			continue;
		}

		int cSocketfd;
		if(socket_accept(socketfd,cSocketfd) != -1)
		{
			if(event(cSocketfd) == 0)
			{
				continue;
			}
			else
			{
				return;
			}

			usleep(1*1000*1000);
			continue;
		}
	}

	return;
}

void server_open(int(*event)(int))
{
	while(true)
	{
		int socketfd;

		if(socket_open("127.0.0.1",42890,socketfd) != 0)
		{
			printf("\nread ==============socket_listen error!");
			continue;
		}

		wait_use_select(socketfd,event);
		socket_close(socketfd);
	}

	return;
}


