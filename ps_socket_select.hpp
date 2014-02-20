#include <sys/select.h>

int wait_use_select(int socketfd,int(*event)(int))
{
	fd_set fd;
	struct timeval tv;

	/* 等待连接次数 */
	int count = 0;

	while(true)
	{
		printf("\n==============wait_use_select() : this is the %dth call select()",++count);

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
				return -1;
			}

			usleep(1*1000*1000);
			continue;
		}
	}

	return 0;
}
