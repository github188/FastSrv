/*
//
//	Last Modify Date: 2015-09-17
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


bool AccepterHandle::msg_upload(const protocol::Packet* in, protocol::Packet* out)
{
	out->ptrHead->command_id = protocol::data::MSG_UPLOAD_REP;

	// if(!r->redis_hset("strKey", "strField", "strValue"))
	// 	return false;

	return true;
}
