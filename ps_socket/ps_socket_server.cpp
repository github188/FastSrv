
#include "ps_socket_api.h"

void socket_server_open(int(*event)(int),const char* host,const unsigned short port)
{
	while(true)
	{
		int socketfd;

		if(socket_open(host,port,socketfd) != 0)
		{
			printf("\n[ps_socket] socket_listen error!");
			usleep(1*1000*1000);
			continue;
		}

		int flag = socket_wait_by_select(socketfd,event);
		socket_close(socketfd);

		if(flag == 1)
		{
			return;
		}
	}

	return;
}

