/*
//
//	Last Modify Date: 2015-10-14
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
	session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
	session::node n = hbm->getSlave();
	LOG_DEBUG("assign server [ip = " << n.ip << ", port = " << n.port << ", load = " << n.load << "] to machine " << out->getDevId());

	return session::HANDLE_RTN_CONTINUE;
}
