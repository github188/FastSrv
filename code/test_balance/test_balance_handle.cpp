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

bool BalanceHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
{
	out->copyHead(in);

	if(in->ptrHead->command_id == protocol::data::MSG_CUTOVER_REP)
	{
		return msg_cutover(in, out);
	}

	return false;
}


bool BalanceHandle::msg_cutover_rep(const protocol::Packet* in, protocol::Packet* out)
{
	// TODO 打印收到的 time 即可

	return true;
}
