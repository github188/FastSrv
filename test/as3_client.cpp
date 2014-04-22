/* 
** 
** client 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "ps_task_api.h"
#include "ps_socket_api.h"
#include "ps_protocol_as3_api.h"
#include "as3_message.h"

int event_request(int socketfd,char* sendBuf,char* recvBuf);

int main()
{
	int socketfd;

	if(socket_connect("127.0.0.1",8888,socketfd,10,5) != 0)
	{
		printf("\n[test] socket_connect error!\n");
		socket_close(socketfd);
		return 0;
	}

	printf("\n[test] server connect!\n");

	/* request 1 */
	char sendBuf[512] = "<key>1</key>";
	char recvBuf[512] = {'\0'};
	event_request(socketfd,sendBuf,recvBuf);

	/* request 2 */
	memset(sendBuf,'\0',512);
	memset(recvBuf,'\0',512);
	strncpy(sendBuf,"<key1><node1>value1</node1><node2>value2</node2></key1>",512);
	event_request(socketfd,sendBuf,recvBuf);

	socket_close(socketfd);

	printf("\n");

	return 0;
}

int event_request(int socketfd,char* sendBuf,char* recvBuf)
{
	memset(recvBuf,'\0',512);

	printf("\n[test] client send : %s\n",sendBuf);
	protocol_as3_send(socketfd,sendBuf,strlen(sendBuf));
	protocol_as3_recv(socketfd,recvBuf);
	printf("[test] client receive : %s\n",recvBuf);

	return 0;
}

