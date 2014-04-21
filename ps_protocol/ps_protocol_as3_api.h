#ifndef __PS_PROTOCOL_AS3_API_H__
#define __PS_PROTOCOL_AS3_API_H__

#include "ps_socket_api.h"

/* data */
int protocol_as3_recv(int socketfd,char* buf);
int protocol_as3_send(int socketfd,char* buf,size_t nbytes);

/* as3 */
int protocol_as3_check_843(int socketfd);

// __PS_PROTOCOL_AS3_API_H__
#endif
