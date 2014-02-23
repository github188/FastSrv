/* 
** 
** client 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "../ps_api.h"
#include "ps_message.h"

int event_request(int socketfd);
int event_login(int socketfd);

int main()
{
	int socketfd;

	if(socket_connect("127.0.0.1",42890,socketfd,10,5) != 0)
	{
		printf("\n==============socket_connect error!\n");
		socket_close(socketfd);
		return 0;
	}

	if(event_login(socketfd) == 0)
	{
		event_request(socketfd);
	}

	socket_close(socketfd);

	printf("\n");

	return 0;
}

int event_login(int socketfd)
{
	st_head sth;

	memset(&sth,'\0',sizeof(st_head));
	memcpy(sth.auth,"zengpw",9);
	memcpy(sth.version,"0.1",9);
	memcpy(sth.response,"0",4);

	socket_send_normal(socketfd,(char*)&sth,sizeof(st_head));
	socket_recv_normal(socketfd,(char*)&sth,sizeof(st_head));

	if(strncmp(sth.response,"1",5))
	{
		printf("\n==============identity verify error!");
		return -1;
	}

	printf("\n==============server is ready!");
	return 0;
}

int event_request(int socketfd)
{
	st_body sth;

	memset(&sth,'\0',sizeof(st_body));
	memcpy(sth.question,"AABBCCDD",99);

	printf("\n==============send the question after 3 seconds !");
	usleep(3*1000*1000);
	socket_send_normal(socketfd,(char*)&sth,sizeof(st_body));
	socket_recv_normal(socketfd,(char*)&sth,sizeof(st_body));

	printf("\n==============Server is reponse ! \n==============\"%s\"",sth.answer);

	return 0;
}
