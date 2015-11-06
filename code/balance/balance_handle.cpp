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
		session::HeartBeatMsg* hbm = session::HeartBeatMsg::instance();
		session::node n = hbm->getSlave();
		LOG_DEBUG("fast server : ip = " << n.ip << ", port = " << n.port << ", load = " << n.load);

		stringstream ss;

		memset(para.addr, 0, sizeof(para.addr));
		ss << n.ip;
		ss >> para.addr;
		ss.str("");
		ss.clear();

		memset(para.port, 0, sizeof(para.port));
		ss << n.port;
		ss >> para.port;
		ss.str("");
		ss.clear();

		out->add(TID_PARAMETER, sizeof(TLV_PARAMETER), (char*)&para);
		out->build();

		//只要数据库能够连接，不论 redis 是否能够连接，均发送服务器信息
		if(rc->redis_lpush("msg_upload", in->getMsg(), in->getMsgLen()) != 0)
		{
			LOG_DEBUG("redis push occur serious error, please check redis!");
		}
	}

	LOG_DEBUG("send server address to terminal " << in->getDevId() << ", ip = " << para.addr << ", port = " << para.port);

	return session::HANDLE_RTN_SEND;
}
