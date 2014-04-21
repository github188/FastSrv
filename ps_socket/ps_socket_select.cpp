
#include "ps_socket_api.h"

int socket_wait_by_select(int socketfd,int(*event)(int))
{
	fd_set fd;
	struct timeval tv;

	while(true)
	{
		FD_ZERO(&fd);
		FD_SET(socketfd,&fd);
		tv.tv_sec = 0;
		tv.tv_usec = 100000;

		if(select(socketfd+1,&fd,NULL,NULL,&tv) <= 0)
		{
			continue;
		}

		int cSocketfd;
		if(socket_accept(socketfd,cSocketfd) != -1)
		{
			int flag = event(cSocketfd);

			if(flag == 0)
			{
				continue;
			}
			else if(flag == 1)
			{
				return 1;
			}
			else
			{
				return -1;
			}

			usleep(1*1000*1000);
			continue;
		}
	}

	return 0;
}


