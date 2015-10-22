/*
//
//	Last Modify Date: 2015-10-15
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息入队
//
//
*/

#include "task_handle.h"

void TaskHandle::shortResponse(protocol::PacketOut* out, int success)
{
	TLV_RTN rtn = 1;
	out->add(TID_RTN, sizeof(TLV_RTN), (char*)&rtn);
	out->build();
}


session::HANDLE_RTN TaskHandle::flashPush(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	if(rc->redis_lpush("msg_upload", in->getMsg(), in->getMsgLen()) == 0)
	{
		shortResponse(out, 1);
		return session::HANDLE_RTN_SEND;
	}
	else
	{
		LOG_DEBUG("redis push occur serious error, please check redis!");
		shortResponse(out, 0);
		return session::HANDLE_RTN_STOP;
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TaskHandle::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return flashPush(in, out);
}


session::HANDLE_RTN TaskHandle::cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return flashPush(in, out);
}
