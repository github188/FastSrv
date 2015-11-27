/*
//
//	Last Modify Date: 2015-11-19
//	Author: zengpw
//	History:
//					2015-10-10 zengpw created
//	File Property: public
//	Future:
//					I. 封装从 redis 队列存取数据事件
//
//
*/

#include "redis_queue.h"

namespace session
{
	RedisQueue::RedisQueue(const string ip, const unsigned int port)
	{
		rc = NULL;
		this->ip = ip;
		this->port = port;
	}

	RedisQueue::RedisQueue(const string ip, const unsigned int port, HandleBasic* hb)
	{
		rc = NULL;
		this->ip = ip;
		this->port = port;
		this->hb = hb;
	}

	common::Redis* RedisQueue::open()
	{
		rc = new common::Redis(ip, port);
		if(rc->redis_conn() != 0)
		{
			LOG_DEBUG("RedisQueue : open() error!");
			delete rc;
			rc = NULL;
		}
		return rc;
	}

	int RedisQueue::run()
	{
		if(open() == NULL)
			return 0;

		LOG_DEBUG("get data from msg_upload_redo!");

		for(;;)
		{
			memset(buffer, 0, sizeof(buffer));
			len = 0;

			int rtn = rc->redis_rpoplpush("msg_upload_redo", "msg_upload_error", buffer, &len);

			if(rtn == -1)
			{
				LOG_DEBUG("RedisQueue : get data from msg_upload_redo error!");
				return -1;
			}

			if(rtn == 1)
			{
				break;
			}

			if(rtn == 0)
			{
				protocol::PacketIn *in = new protocol::PacketIn;
				protocol::PacketOut *out = new protocol::PacketOut;

				int rt = hb->dispatch_origin_msg(buffer, len, in, out);

				if(rt == HANDLE_RTN_CONTINUE)
				{
					delete in;
					delete out;
					continue;
				}

				if(rt == HANDLE_RTN_REMOVE)
				{
					rc->redis_lrem("msg_upload_error", buffer, len);

					delete in;
					delete out;
					continue;
				}

				if(rt == HANDLE_RTN_STOP)
				{
					delete in;
					delete out;
					return 0;
				}
			}
		}

		LOG_DEBUG("get data from msg_upload!");

		for(;;)
		{
			memset(buffer, 0, sizeof(buffer));
			len = 0;

			int rtn = rc->redis_rpoplpush("msg_upload", "msg_upload_redo", buffer, &len);

			if(rtn == -1)
			{
				LOG_DEBUG("RedisQueue : get data from msg_upload error!");
				return -1;
			}

			if(rtn == 1)
			{
				usleep(5*1000*1000);
			}

			if(rtn == 0)
			{
				protocol::PacketIn *in = new protocol::PacketIn;
				protocol::PacketOut *out = new protocol::PacketOut;

				int rt = hb->dispatch_origin_msg(buffer, len, in, out);

				if(rt == HANDLE_RTN_CONTINUE)
				{
					delete in;
					delete out;
					continue;
				}

				if(rt == HANDLE_RTN_REMOVE)
				{
					rc->redis_lrem("msg_upload_redo", buffer, len);

					delete in;
					delete out;
					continue;
				}

				if(rt == HANDLE_RTN_STOP)
				{
					delete in;
					delete out;
					return 0;
				}
			}
		}

		return 0;
	}
};// namespace session