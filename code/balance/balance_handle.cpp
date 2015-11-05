/*
//
//	Last Modify Date: 2015-11-05
//	Author: zengpw
//	History:
//					2015-08-26 zengpw created
//	File Property: public
//	Future:
//					I. 负载均衡消息处理
//
//
*/

#include "balance_handle.h"

session::HANDLE_RTN BalanceHandle::cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	session::DbPublic dp;

	out->setCID(CID_LOGIN);

	//时间
	DateTimeSec dts = buildDateTimeSec();
	out->add(TID_TIME, sizeof(DateTimeSec), (char*)&dts);

	//运行参数
	TLV_PARAMETER para;

	if(!dp.public_get_parameter_request(db, in->getDevId(), para))
	{
		return session::HANDLE_RTN_CONTINUE;
	}
	else
	{
		memset(para.addr, 0, sizeof(para.addr));
		strncpy((char*)para.addr, "220.248.44.218", 15);

		memset(para.port, 0, sizeof(para.port));
		strncpy((char*)para.port, "21010", 5);

		out->add(TID_PARAMETER, sizeof(TLV_PARAMETER), (char*)&para);
	}

	out->build();

	return session::HANDLE_RTN_SEND;
}
