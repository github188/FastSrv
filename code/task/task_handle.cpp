/*
//
//	Last Modify Date: 2015-11-06
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

session::HANDLE_RTN TaskHandle::push(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	if(rc_upload->redis_lpush("msg_upload", in->getMsg(), in->getMsgLen()) == 0)
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

session::HANDLE_RTN TaskHandle::flashPush(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	if(rc_upload->redis_lpush("msg_upload", in->getMsg(), in->getMsgLen()) != 0)
	{
		LOG_DEBUG("redis push occur serious error, please check redis!");
		return session::HANDLE_RTN_STOP;
	}

	return session::HANDLE_RTN_CONTINUE;
}

void TaskHandle::rename(string& key)
{
	string end = common::buildDateTime();
	string new_key = key + "_";
	new_key += end;

	if(rc_sending->redis_rename(key.c_str(), new_key.c_str()) == 0)
	{
		//修改 sts ，修改 end time
		// sts =0 初始状态； =1 下发成功； =2 未下发，被新的命令覆盖
		rc_sending->redis_hmset4update(new_key.c_str(), end.c_str(), "1");
	}
}

session::HANDLE_RTN TaskHandle::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return push(in, out);
}

session::HANDLE_RTN TaskHandle::cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return push(in, out);
}

session::HANDLE_RTN TaskHandle::cidDataTh(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return push(in, out);
}

session::HANDLE_RTN TaskHandle::cidUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return flashPush(in, out);
}

session::HANDLE_RTN TaskHandle::cidDevUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return push(in, out);
}

session::HANDLE_RTN TaskHandle::cidDevband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	session::DbPublic dp;

	out->setCID(CID_DEV_BAND);

	//时间
	DateTimeSec dts = buildDateTimeSec();
	out->add(TID_TIME, sizeof(DateTimeSec), (char*)&dts);

	//订单号
	string order_id;
	TLV_ORDER_ID order;

	if(!dp.public_get_order_id(db, in->getDevId(), order_id))
	{
		return session::HANDLE_RTN_CONTINUE;
	}
	else
	{
		memset(order, 0, sizeof(order));
		memcpy(order, order_id.c_str(), sizeof(order));
		out->add(TID_ORDER_ID, sizeof(TLV_ORDER_ID), (char*)&order_id);
	}

	//运行参数
	TLV_PARAMETER para;

	if(!dp.public_get_parameter_request(db, in->getDevId(), para))
		return session::HANDLE_RTN_CONTINUE;
	else
		out->add(TID_PARAMETER, sizeof(TLV_PARAMETER), (char*)&para);

	out->build();

	return session::HANDLE_RTN_SEND;
}

session::HANDLE_RTN TaskHandle::sending(const protocol::PacketIn* in, vector<protocol::PacketOut> &vp)
{
	string keys = in->getDevId() + "_*";
	vector<string> vs;

	if(rc_sending->redis_keys(keys, vs) == 0)
	{
		for(int i = 0; i < vs.size(); i++)
		{
			protocol::PacketOut out;
			out.copy(in);

			LOG_DEBUG("matching command = " << vs[i]);

			//解绑
			if(vs[i] == in->getDevId() + "_3")
			{
				if(sendUnband(in, &out) == session::HANDLE_RTN_SEND)
				{
					LOG_DEBUG("build message : redis key = " << vs[i]);
					vp.push_back(out);
					rename(vs[i]);
				}
			}

			//运行参数下发
			if(vs[i] == in->getDevId() + "_6")
			{
				if(sendParameter(in, &out) == session::HANDLE_RTN_SEND)
				{
					vp.push_back(out);
					rename(vs[i]);
				}
			}

			//版本升级
			if(vs[i] == in->getDevId() + "_8")
			{
				if(sendVersion(in, &out) == session::HANDLE_RTN_SEND)
				{
					vp.push_back(out);
					rename(vs[i]);
				}
			}

			//初始化
			if(vs[i] == in->getDevId() + "_9")
			{
				if(sendInit(in, &out) == session::HANDLE_RTN_SEND)
				{
					vp.push_back(out);
					rename(vs[i]);
				}
			}
		}
	}

	return session::HANDLE_RTN_SEND;
}

session::HANDLE_RTN TaskHandle::sendUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	out->setCID(CID_UNBAND);
	DateTimeSec dts = buildDateTimeSec();
	out->add(TID_TIME, sizeof(DateTimeSec), (char*)&dts);
	out->build();

	return session::HANDLE_RTN_SEND;
}

session::HANDLE_RTN TaskHandle::sendParameter(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return session::HANDLE_RTN_CONTINUE;
}

session::HANDLE_RTN TaskHandle::sendVersion(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return session::HANDLE_RTN_CONTINUE;
}

session::HANDLE_RTN TaskHandle::sendInit(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	return session::HANDLE_RTN_CONTINUE;
}