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

session::SESSION_RTN BalanceHandle::msg_cutover(const protocol::Packet* in, protocol::Packet* out)
{
	out->ptrHead->command_id = protocol::data::MSG_CUTOVER_REP;

	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::node n = hbm->getSlave();
	LOG_DEBUG("assign server [ip = " << n.ip << ", port = " << n.port << ", load = " << n.load << "] to machine " << out->ptrHead->device_id);

	// protocol::data::TLVPtr ptrTLV = out->setTLV(8, 6);
	// out->setCRC();

	return session::SESSION_RTN_SEND;
}
