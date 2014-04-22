/* 
** 
** server 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "ps_task_api.h"
#include "ps_socket_api.h"
#include "ps_protocol_as3_api.h"
#include "as3_message.h"

void* event_response(void* arg);
int event_accept_t(int socketfd);
void* event_accept(void* arg);
void* event_843(void* arg);

int main()
{
	if(task_init() == 0)
	{
		if(thread_pool_init() == 0)
		{
			thread_pool_add(1,event_843);
			thread_pool_add(1,event_accept);
			thread_pool_add(1,event_response);
		}
	}

	while(true)
	{
		;
	}

	return 0;
}

void* event_843(void* arg)
{
	socket_server_open(protocol_as3_check_843,"127.0.0.1",843);
	return NULL;
}

void* event_accept(void* arg)
{
	socket_server_open(event_accept_t,"127.0.0.1",8888);
	return NULL;
}

int event_accept_t(int socketfd)
{
	while(true)
	{
		char recvBuf[512] = {'\0'};

		if(protocol_as3_recv(socketfd,recvBuf) <= 0)
		{
			break;
		}

		st_task* stTask = (st_task*)malloc(sizeof(st_task));
		stTask->socketfd = socketfd;
		strncpy(stTask->szBuf,recvBuf,512);

		if(task_push((void*)stTask) == 0)
		{
			printf("\n[test] push task : %s\n",stTask->szBuf);
		}
		else
		{
			printf("\n[test] push the request to pool error!\n");
			return -1;
		}		
	}

	return 0;
}

void* event_response(void* arg)
{
	while(true)
	{
		usleep(1*1000*1000);
		void* stTask_t = NULL;
		if(task_pop(&stTask_t) == 0)
		{
			st_task* stTask = (st_task*)stTask_t;
			printf("\n[test] pop task : %s\n",stTask->szBuf);

			char sendBuf[512] = {'\0'};
			strncpy(sendBuf,"I get your message!",512);
			protocol_as3_send(stTask->socketfd,sendBuf,strlen(sendBuf));
			free(stTask);
		}
	}

	return NULL;
}


