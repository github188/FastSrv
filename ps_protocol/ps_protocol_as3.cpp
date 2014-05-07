
#include "ps_protocol_as3_api.h"

int protocol_as3_recv(int socketfd,char* buf)
{
	int received = 0;
	int offset = 0;

	while(true)
	{
		received = 0;
		received = (int)recv(socketfd,buf + offset,1,0);
		if(received <= 0)
		{
			return -1;
		}
		offset = offset + received;

		//判断读入的字符
		if(strncmp(buf + offset - 1,"\0",1) == 0)
			break;

		if(strncmp(buf + offset - 1,"\n",1) == 0)
			break;
	}

	return offset;
}

int protocol_as3_send(int socketfd,char* buf,size_t nbytes)
{
	char sendBuf[1024] = {'\0'};
	snprintf(sendBuf,nbytes + 1,"%s%c",buf,'\0');
	return socket_send_by_size(socketfd,sendBuf,nbytes + 1);
}

int protocol_as3_check_843(int socketfd)
{
	char recvBuf[512] = {'\0'};
	char sendBuf[512] = {'\0'};

	protocol_as3_recv(socketfd,recvBuf);

	if(strncmp(recvBuf,"<policy-file-request/>",22) == 0)
	{
		printf("\n[ps_protocol_as3] receive policy request! ");
		strncpy(sendBuf,"<?xml version=\"1.0\"?><cross-domain-policy><site-control permitted-cross-domain-policies=\"all\"/><allow-access-from domain=\"*\" to-ports=\"*\"/></cross-domain-policy>",512);
		protocol_as3_send(socketfd,sendBuf,strlen(sendBuf));
		printf("\n[ps_protocol_as3] send policy allow : %s",sendBuf);
	}

	return 0;
}

