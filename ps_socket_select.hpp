#include <sys/select.h>

int wait_use_select(int theSocket,void*(*event)())
{
	int flag;
	fd_set fd;
	struct timeval tv;

	while(true)
	{
		flag = 0;
		FD_ZERO(&fd);
		FD_SET(theSocket,&fd);
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		flag = select(theSocket+1,&fd,NULL,NULL,&tv);
		if(flag <= 0)
		{
			continue;
		}

		int clientSocket;
		clientSocket = socket_accept(theSocket);

		if(clientSocket != -1)
		{
			usleep(5000);
			continue;
		}
	}

	return 0;
}

