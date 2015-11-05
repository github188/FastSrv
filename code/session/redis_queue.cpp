/*
//
//	Last Modify Date: 2015-10-30
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
	RedisQueue::RedisQueue(const string ip, const unsigned int port, common::Thread* th, HandleBasic* hb)
	{
		rc = NULL;
		this->th = NULL;
		this->hb = NULL;

		this->ip = ip;
		this->port = port;
		this->th = th;
		this->hb = hb;
	}


	common::Redis* RedisQueue::getRedisConn()
	{
		rc = new common::Redis(ip, port);

		if(rc->redis_conn() != 0)
		{
			LOG_DEBUG("redis connect error");
			delete rc;
			rc = NULL;
		}

		return rc;
	}


	void RedisQueue::start()
	{
		th->create(queueCb, (void*)this);
	}


	void* RedisQueue::queueCb(void* self)
	{
		RedisQueue* rq = (RedisQueue*)self;

		//作用于线程的 redis 对象
		common::Redis* rc = new common::Redis(rq->ip, rq->port);

		if(rc->redis_conn() != 0)
		{
			LOG_DEBUG("connect redis error");
			return NULL;
		}

		HandleBasic* hb = rq->hb;

		while(true)
		{
			// LOG_DEBUG("=========== pop data from redis ===========");

			rq->len = 0;
			memset(rq->queue, 0, sizeof(rq->queue));

			int rtn = rc->redis_rpoplpush("msg_upload", "msg_upload_backup", rq->queue, &rq->len);

			if(rtn == -1)
			{
				LOG_DEBUG("handleCb call redis_rpoplpush fail! thread exit!");
				return NULL;
			}

			if(rtn == 1)
			{
				// LOG_DEBUG("handleCb call redis_rpoplpush return empty! sleep 5000ms");
				usleep(5*1000*1000);
			}

			if(rtn == 0)
			{
				protocol::PacketIn *in = new protocol::PacketIn;
				protocol::PacketOut *out = new protocol::PacketOut;

				int rt = hb->dispatch_origin_msg(rq->queue, rq->len, in, out);

				if(rt == HANDLE_RTN_SEND)
				{
					//发送 out 报文（走 redis 发送），删除原数据
				}

				if(rt == HANDLE_RTN_CONTINUE)
				{
					delete in;
					delete out;
					continue;
				}

				if(rt == HANDLE_RTN_REMOVE)
				{
					delete in;
					delete out;
					// TODO : 删除 redis 中原数据
					continue;
				}

				if(rt == HANDLE_RTN_STOP)
				{
					delete in;
					delete out;
					return NULL;
				}

				return NULL;
			}
		}
	}
};// namespace session