/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息预处理
//
//
*/

#include "accepter_handle.h"

bool AccepterHandle::redis_init(string ip, unsigned int port)
{
	r = new common::Redis(ip, port);

	if(r->redis_conn() != 0)
		return false;

	return true;
}


session::SESSION_RTN AccepterHandle::msg_upload(const protocol::Packet* in, protocol::Packet* out)
{
	if(r->redis_lpush("msg_upload", in->raw(), in->len()) == 0)
	{
		// TODO 返回接收正确的报文
		return session::SESSION_RTN_CONTINUE;
	}
	else
	{
		LOG_DEBUG("redis push occur serious error, program exit!");
		return session::SESSION_RTN_STOP;
	}

	return session::SESSION_RTN_CONTINUE;
}
