/*
//
//	Last Modify Date: 2015-09-18
//	Author: zengpw
//	History:
//					2015-09-18 zengpw created
//	File Property: public
//	Future:
//					I. 负载均衡测试
//
//
*/

#include "test_balance_handle.h"

session::SESSION_RTN BalanceHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
{
	out->copyHead(in);

	if(in->ptrHead->command_id == protocol::data::MSG_CUTOVER_REP)
	{
		return msg_cutover(in, out);
	}

	return session::SESSION_RTN_CONTINUE;
}


session::SESSION_RTN BalanceHandle::conn(protocol::Packet* out)
{
	LOG_DEBUG("BalanceHandle conn");

	return session::SESSION_RTN_CONTINUE;
}


session::SESSION_RTN BalanceHandle::msg_cutover_rep(const protocol::Packet* in, protocol::Packet* out)
{
	// TODO 打印收到的 time 即可

	return session::SESSION_RTN_CONTINUE;
}
