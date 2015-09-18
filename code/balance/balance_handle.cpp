/*
//
//	Last Modify Date: 2015-09-18
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

bool BalanceHandle::msg_cutover(const protocol::Packet* in, protocol::Packet* out)
{
	out->ptrHead->command_id = protocol::data::MSG_CUTOVER_REP;

	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::node n = hbm->getSlave();
	printf("\n assign server [ip = %s, port = %d, load = %d] to machine %12s \n", \
		n.ip.c_str(), n.port, n.load, out->ptrHead->device_id);

	// protocol::data::TLVPtr ptrTLV = out->setTLV(8, 6);
	// out->setCRC();

	return true;
}
