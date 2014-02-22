/* 
** 
** server 端的例子
** 编译请使用compile目录下的bulid.sh
**
*/

#include "../ps_api.h"
#include "ps_message.h"

void* event_response(void* arg);
int event_accept_t(int socketfd);
void* event_accept(void* arg);

int main()
{
	task_init();
	thread_pool_init();
	thread_pool_add(1,event_accept);
	thread_pool_add(1,event_response);
	printf("\n");
	return 0;
}

void* event_accept(void* arg)
{
	server_open(event_accept_t);
	return NULL;
}

int event_accept_t(int socketfd)
{
	//登陆
	st_head st_head_t;
	socket_recv_normal(socketfd,(char*)&st_head_t,sizeof(st_head));

	printf("\nread ==============receive st_head_t.auth : %s",st_head_t.auth);
	printf("\nread ==============receive st_head_t.version : %s",st_head_t.version);

	if(strncmp(st_head_t.auth,"zengpw",10) || strncmp(st_head_t.version,"0.1",10))
	{
		printf("\nread ==============identity verify error!");
		memcpy(st_head_t.response,"0",4);
		socket_send_normal(socketfd,(char*)&st_head_t,sizeof(st_head));
		return -1;
	}

	//登陆响应
	memcpy(st_head_t.response,"1",4);
	socket_send_normal(socketfd,(char*)&st_head_t,sizeof(st_head));
	printf("\nread ==============client is allow to login");

	//接收包体
	st_body* st_body_t = (st_body*)malloc(sizeof(st_body));
	socket_recv_normal(socketfd,(char*)st_body_t,sizeof(st_body));

	st_task* st_task_t = (st_task*)malloc(sizeof(st_task));
	st_task_t->st_body_t = st_body_t;
	st_task_t->socketfd = socketfd;

	if(task_push((void*)st_task_t) == 0)
	{
		printf("\nread ==============push question : %s",st_body_t->question);
		printf("\nread ==============I'll push the request to pool");
	}
	else
	{
		printf("\nread ==============Push the request to pool error!");
		return -1;
	}

	return 0;
}

void* event_response(void* arg)
{
	while(true)
	{
		printf("\ndeal ==============I'll pop the request from pool");

		void* task = NULL;
		if(!task_pop(task))
		{
			st_task* st_task_t = (st_task*)task;
			printf("\ndeal ==============pop question : %s",st_task_t->st_body_t->question);

			char ch[256] = {'\0'};
			memcpy(ch,st_task_t->st_body_t->question,99);
			memcpy(st_task_t->st_body_t->answer,"I'm the server,I recevie your quesion is : ",99);
			strcat(st_task_t->st_body_t->answer,ch);
			socket_send_normal(st_task_t->socketfd,(char*)st_task_t->st_body_t,sizeof(st_body));
		}

		printf("\ndeal ==============pop after 5 seconds");
		usleep(5*1000*1000);
	}

	return NULL;
}


