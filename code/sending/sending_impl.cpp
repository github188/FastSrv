/*
//
//	Last Modify Date: 2015-11-03
//	Author: zengpw
//	History:
//					2015-10-28 zengpw created
//	File Property: private
//	Future:
//					I. 实现 ICE 的接口
//
//
*/

#include "sending_impl.h"

void SendingImpl::setRedis(common::Redis* rc)
{
	this->rc = rc;
}

::sending::server::Rtn SendingImpl::buildRtn(int e, string str)
{
	::sending::server::Rtn r;

	r.e = e;
	r.str = str;

	LOG_DEBUG("build : r.e = " << r.e << ", r.str = " << r.str);
	return r;
}

::sending::server::Rtn SendingImpl::push(const ::sending::server::Command& cmd, const ::Ice::Current& c)
{
	::sending::server::Rtn r;

	LOG_DEBUG("receive : cmd.id = " << cmd.id << ", cmd.type = " << cmd.type);

	// 解绑 3
	// 运行参数下发 6
	// 版本升级 8
	// 初始化 9
	if(cmd.type == 3 || cmd.type == 6 || cmd.type == 8 || cmd.type == 9)
	{
		string key = cmd.id + "_";

		string id;
		stringstream ss;
		ss << cmd.type;
		id = ss.str();
		ss.str("");
		ss.clear();

		key += id;

		LOG_DEBUG("-------------------------- sending command begin --------------------------");

		if(rc->redis_select(0) != 0)
			return buildRtn(-2, "redis select error!");

		//处理未下发命令
		int rtn = rc->redis_exists(key.c_str());

		if(rtn == 1)
		{
			if(rc->redis_move(key.c_str(), 1) != 0)
				return buildRtn(-4, "redis move error!");
			else
			{
				if(rc->redis_select(1) != 0)
					return buildRtn(-2, "redis select error!");

				//修改 key name
				string new_key = key + "_";
				new_key += common::buildDateTime();

				if(rc->redis_rename(key.c_str(), new_key.c_str()) == 0)
				{
					//修改 sts ，修改 end time
					// sts =0 初始状态； =1 下发成功； =2 未下发，被新的命令覆盖
					string end = common::buildDateTime();
					if(rc->redis_hmset4update(new_key.c_str(), end.c_str(), "2") != 0)
						return buildRtn(-6, "redis update error!");

					//设置失效时间
					rc->redis_expire(new_key, "2592000");
				}
				else
					return buildRtn(-5, "redis rename error!");

				if(rc->redis_select(0) != 0)
					return buildRtn(-2, "redis select error!");
			}
		}

		//处理已下发命令
		string new_key = key + "_*";
		vector<string> vs;

		if(rc->redis_keys(new_key, vs) == 0)
		{
			for(int i = 0; i < vs.size(); i++)
			{
				if(rc->redis_move(vs[i].c_str(), 1) != 0)
					return buildRtn(-4, "redis move error!");
				else
				{
					if(rc->redis_select(1) != 0)
						return buildRtn(-2, "redis select error!");

					//设置失效时间
					rc->redis_expire(vs[i], "2592000");

					if(rc->redis_select(0) != 0)
						return buildRtn(-2, "redis select error!");
				}
			}
		}

		//调用插入函数
		string begin = common::buildDateTime();

		if(rc->redis_hmset4sending(key.c_str(), begin.c_str(), "0", "0") != 0)
			return buildRtn(-3, "redis insert error!");
		else
			return buildRtn(0, "success");
	}
	else
		return buildRtn(-1, "command type error!");

	return r;
}