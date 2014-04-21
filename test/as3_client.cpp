/* 
** 
** client 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "ps_socket_api.h"
#include "as3_message.h"

int event_request(int socketfd);

int main()
{
	// int socketfd;

	// if(socket_connect("127.0.0.1",843,socketfd,10,5) != 0)
	// {
	// 	printf("\n[test_flash] socket_connect error!\n");
	// 	socket_close(socketfd);
	// 	return 0;
	// }

	// printf("\n[test_flash] server connect!\n");

	// event_request(socketfd);

	// socket_close(socketfd);

	// printf("\n");

	return 0;
}

int event_request(int socketfd)
{
	// char sendBuf[256] = {"<policy-file-request/>\0"};
	// char recvBuf[512] = {'\0'};

	// socket_send_by_size(socketfd,sendBuf,strlen(sendBuf) + 1);
	// socket_recv_by_size(socketfd,recvBuf,sizeof(recvBuf));
	// printf("\n[test_flash] client receiver : %s",recvBuf);

	return 0;
}

