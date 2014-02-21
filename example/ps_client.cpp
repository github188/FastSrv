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

	if(socket_connect("127.0.0.1",42890,socketfd,10,5) != 0)
	{
		printf("\n==============socket_connect error!\n");
		socket_close(socketfd);
		return 0;
	}

	st_head sth;

	memset(&sth,'\0',sizeof(st_head));
	memcpy(sth.auth,"zengpw",9);
	memcpy(sth.version,"0.2",9);

	socket_send_normal(socketfd,(char*)&sth,sizeof(st_head));

	socket_close(socketfd);

	printf("\n");

	return 0;
}

